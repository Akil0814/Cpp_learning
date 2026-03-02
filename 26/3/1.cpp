#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

template <typename t, typename compare>
class my_priority_queue
{
public:
    my_priority_queue() = default;

    explicit my_priority_queue(compare comp): comp_(std::move(comp)){}

    bool empty() const
    {
        return data_.empty();
    }

    std::size_t size() const
    {
        return data_.size();
    }

    const t& top() const
    {
        if (data_.empty())
            throw std::out_of_range("my_priority_queue::top: empty queue");
        return data_.front();
    }

    void push(const t& value)
    {
        data_.push_back(value);
        sift_up_(data_.size() - 1);
    }

    void push(t&& value)
    {
        data_.push_back(std::move(value));
        sift_up_(data_.size() - 1);
    }

    template <typename... args>
    void emplace(args&&... a)
    {
        data_.emplace_back(std::forward<args>(a)...);
        sift_up_(data_.size() - 1);
    }

    void pop()
    {
        if (data_.empty())
            throw std::out_of_range("my_priority_queue::pop: empty queue");

        if (data_.size() == 1)
        {
            data_.pop_back();
            return;
        }

        data_.front() = std::move(data_.back());
        data_.pop_back();
        sift_down_(0);
    }

    void clear()
    {
        data_.clear();
    }

private:
    bool lower_priority_(const t& a, const t& b) const
    {
        return comp_(a, b);
    }

    std::size_t parent_(std::size_t i) const { return (i - 1) / 2; }
    std::size_t left_(std::size_t i) const { return 2 * i + 1; }
    std::size_t right_(std::size_t i) const { return 2 * i + 2; }

    void sift_up_(std::size_t idx)
    {
        while (idx > 0)
        {
            std::size_t p = parent_(idx);

            if (lower_priority_(data_[p], data_[idx]))
            {
                std::swap(data_[p], data_[idx]);
                idx = p;
            }
            else
            {
                break;
            }
        }
    }

    void sift_down_(std::size_t idx)
    {
        const std::size_t n = data_.size();
        while (true)
        {
            std::size_t l = left_(idx);
            std::size_t r = right_(idx);
            std::size_t best = idx;

            if (l < n && lower_priority_(data_[best], data_[l]))
                best = l;
            if (r < n && lower_priority_(data_[best], data_[r]))
                best = r;

            if (best != idx)
            {
                std::swap(data_[idx], data_[best]);
                idx = best;
            }
            else
            {
                break;
            }
        }
    }

private:
    std::vector<t> data_{};
    compare comp_{};
};

struct patient
{
    std::string name{};
    bool has_life_threat = false;
    int arrival_time_min = 0;
    int remaining_time_min = 25;
};

struct treatment_log
{
    std::string patient_name{};
    int start_min = 0;
    int end_min = 0;
    bool interrupted = false;
};

static void print_time(int min_from_noon)
{
    int total_min = 12 * 60 + min_from_noon;
    int hour24 = (total_min / 60) % 24;
    int minute = total_min % 60;

    bool pm = hour24 >= 12;
    int hour12 = hour24 % 12;
    if (hour12 == 0) hour12 = 12;

    std::cout << hour12 << ":" << std::setw(2) << std::setfill('0') << minute
              << (pm ? " PM" : " AM");
}

struct life_event
{
    int time_min = 0;
    patient p{};
};

auto patient_cmp = [](const patient& a, const patient& b)
{
    return a.arrival_time_min > b.arrival_time_min;
};

int main()
{
    std::priority_queue<patient, std::vector<patient>, decltype(patient_cmp)> patient_queue(patient_cmp);
    //my_priority_queue<patient, decltype(patient_cmp)> patient_queue(patient_cmp);

    std::vector<life_event> life_events;
    size_t next_event_idx = 0;

    std::queue<patient> life_queue;

    patient_queue.push(patient{"Bob Bleeding", false, -360, 25});
    patient_queue.push(patient{"Frank Feelingbad", false, -180, 25});
    patient_queue.push(patient{"Cathy Coughing", false, -300, 25});
    patient_queue.push(patient{"Paula Pain", false, -240, 25});
    patient_queue.push(patient{"Alice Ailment", false, -420, 25});
    patient_queue.push(patient{"Irene Ill", false, -60, 25});
    patient_queue.push(patient{"Tom Temperature", false, -480, 25});

    life_events.push_back(life_event{132, patient{"Sid Sickly", true, 0, 25}});
    life_events.push_back(life_event{94,  patient{"Sam Sneezing", true, 0, 25}});

    std::sort(life_events.begin(), life_events.end(),
              [](const life_event& a, const life_event& b) { return a.time_min < b.time_min; });

    int now_min = 0;
    std::vector<treatment_log> logs;

    bool has_current = false;
    patient current{};

    auto push_due_life_events = [&](int t_now)
    {
        while (next_event_idx < life_events.size() && life_events[next_event_idx].time_min <= t_now)
        {
            life_queue.push(life_events[next_event_idx].p);
            ++next_event_idx;
        }
    };

    push_due_life_events(now_min);

    while (!life_queue.empty() || !patient_queue.empty() || has_current || next_event_idx < life_events.size())
    {
        // 没有正在治疗的人，就选下一个（病危优先）
        if (!has_current)
        {
            if (!life_queue.empty())
            {
                current = life_queue.front();
                life_queue.pop();
                has_current = true;
            }
            else if (!patient_queue.empty())
            {
                current = patient_queue.top();
                patient_queue.pop();
                has_current = true;
            }
            else
            {
                // 没人可治，但未来还有事件：直接跳到下一个事件时间
                now_min = life_events[next_event_idx].time_min;
                push_due_life_events(now_min);
                continue;
            }
        }

        // 在开始这一段治疗前，如果当前时刻就有病危事件，先入队（并在下一轮抢占）
        push_due_life_events(now_min);

        // 如果此刻 life_queue 非空且 current 不是病危，按规则应立即让病危优先
        if (!life_queue.empty() && !current.has_life_threat)
        {
            // current 还没开始治疗（0分钟），直接把它丢回普通队列
            patient_queue.push(current);
            current = life_queue.front();
            life_queue.pop();
            has_current = true;
        }

        // 计算本段治疗会持续到什么时候：治完 or 下一个病危事件到来
        int t_finish = now_min + current.remaining_time_min;

        int t_next_life = std::numeric_limits<int>::max();
        if (next_event_idx < life_events.size())
            t_next_life = life_events[next_event_idx].time_min;

        int t_end = std::min(t_finish, t_next_life);

        // 记录日志
        treatment_log log;
        log.patient_name = current.name;
        log.start_min = now_min;
        log.end_min = t_end;
        log.interrupted = (t_next_life < t_finish && t_end == t_next_life);
        logs.push_back(log);

        // 扣时间、推进时间
        int treated = t_end - now_min;
        current.remaining_time_min -= treated;
        now_min = t_end;

        // 到达 t_end 后，把“恰好在此刻发生”的事件入队（重要：保证抢占发生）
        push_due_life_events(now_min);

        if (log.interrupted)
        {
            // 被打断：没治完的丢回普通队列，病危会在下一轮优先拿到
            if (current.remaining_time_min > 0)
                patient_queue.push(current);

            has_current = false;
        }
        else
        {
            has_current = false;
        }
    }

    std::cout << "Treatment timeline:\n";
    for (const auto& l : logs)
    {
        std::cout << "  " << l.patient_name << "  ";
        print_time(l.start_min);
        std::cout << " - ";
        print_time(l.end_min);
        if (l.interrupted)
            std::cout << "  (interrupted)";
        std::cout << "\n";
    }

    return 0;
}
