#include <cstdint>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

namespace creds_store {

// ---- file format (key at tail) ----
// magic(4) = "CS1D"
// version(1) = 1
// ulen(u32) + uenc bytes
// plen(u32) + penc bytes
// key_obf(1) = key ^ 0x5A   <-- last byte

static constexpr std::uint32_t magic = 0x44533143u; // 'C''S''1''D' in little-endian
static constexpr std::uint8_t version = 1;
static constexpr std::uint8_t key_mask = 0x5Au;

static std::uint8_t obf_key(std::uint8_t k)   { return static_cast<std::uint8_t>(k ^ key_mask); }
static std::uint8_t deobf_key(std::uint8_t k) { return static_cast<std::uint8_t>(k ^ key_mask); }

static void xor_inplace(std::string& s, std::uint8_t key)
{
    for (char& ch : s)
        ch = static_cast<char>(static_cast<std::uint8_t>(ch) ^ key);
}

static std::string xor_copy(const std::string& in, std::uint8_t key)
{
    std::string out = in;
    xor_inplace(out, key);
    return out;
}

static bool write_u32(std::ofstream& out, std::uint32_t v)
{
    out.write(reinterpret_cast<const char*>(&v), sizeof(v));
    return static_cast<bool>(out);
}

static bool read_u32(std::ifstream& in, std::uint32_t& v)
{
    in.read(reinterpret_cast<char*>(&v), sizeof(v));
    return static_cast<bool>(in);
}

static bool write_u8(std::ofstream& out, std::uint8_t v)
{
    out.put(static_cast<char>(v));
    return static_cast<bool>(out);
}

static bool read_u8(std::ifstream& in, std::uint8_t& v)
{
    int c = in.get();
    if (c == EOF) return false;
    v = static_cast<std::uint8_t>(c);
    return true;
}

static bool write_blob(std::ofstream& out, const std::string& s)
{
    out.write(s.data(), static_cast<std::streamsize>(s.size()));
    return static_cast<bool>(out);
}

static bool read_blob(std::ifstream& in, std::string& s, std::uint32_t len)
{
    s.resize(len);
    in.read(s.data(), static_cast<std::streamsize>(len));
    return static_cast<bool>(in);
}

// 单独获取 key（从文件最后 1 byte 读 key_obf，再还原）
bool get_key_from_file(const std::string& filename, std::uint8_t& key_out)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false;

    // 可选但强烈建议：先确认这是我们的文件
    std::uint32_t file_magic = 0;
    std::uint8_t file_version = 0;
    if (!read_u32(in, file_magic)) return false;
    if (file_magic != magic) return false;
    if (!read_u8(in, file_version)) return false;
    if (file_version != version) return false;

    // 去文件末尾读最后 1 byte
    in.seekg(0, std::ios::end);
    std::streamoff size = static_cast<std::streamoff>(in.tellg());
    if (size < 1) return false;

    in.seekg(-1, std::ios::end);

    std::uint8_t key_obf_byte = 0;
    if (!read_u8(in, key_obf_byte)) return false;

    key_out = deobf_key(key_obf_byte);
    return true;
}

bool save_creds(const std::string& user_name, const std::string& password, std::uint8_t key)
{
    std::ofstream out("key.dat", std::ios::binary | std::ios::trunc);
    if (!out)
    {
        std::cerr << "open key.dat failed\n";
        return false;
    }

    const std::string uenc = xor_copy(user_name, key);
    const std::string penc = xor_copy(password, key);

    // header (no key here anymore)
    if (!write_u32(out, magic)) return false;
    if (!write_u8(out, version)) return false;

    // payload
    if (!write_u32(out, static_cast<std::uint32_t>(uenc.size()))) return false;
    if (!write_blob(out, uenc)) return false;

    if (!write_u32(out, static_cast<std::uint32_t>(penc.size()))) return false;
    if (!write_blob(out, penc)) return false;

    // tail: key_obf at last byte
    if (!write_u8(out, obf_key(key))) return false;

    return static_cast<bool>(out);
}

bool load_creds(std::string& user_name, std::string& password)
{
    // 先从尾部把 key 读出来
    std::uint8_t key = 0;
    if (!get_key_from_file("key.dat", key))
    {
        std::cerr << "get_key_from_file failed\n";
        return false;
    }

    std::ifstream in("key.dat", std::ios::binary);
    if (!in)
    {
        std::cerr << "open key.dat failed\n";
        return false;
    }

    // header
    std::uint32_t file_magic = 0;
    if (!read_u32(in, file_magic)) return false;
    if (file_magic != magic)
    {
        std::cerr << "bad file magic\n";
        return false;
    }

    std::uint8_t file_version = 0;
    if (!read_u8(in, file_version)) return false;
    if (file_version != version)
    {
        std::cerr << "unsupported version\n";
        return false;
    }

    // payload
    std::uint32_t ulen = 0, plen = 0;

    if (!read_u32(in, ulen)) return false;
    std::string uenc;
    if (!read_blob(in, uenc, ulen)) return false;

    if (!read_u32(in, plen)) return false;
    std::string penc;
    if (!read_blob(in, penc, plen)) return false;

    // 注意：文件末尾还有 1 byte key_obf，我们不需要再读它

    user_name = xor_copy(uenc, key);
    password  = xor_copy(penc, key);
    return true;
}

void dump_file_hex(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        std::cerr << "cannot read " << filename << "\n";
        return;
    }

    std::vector<std::uint8_t> buf(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    std::cout << filename << " (" << buf.size() << " bytes)\n";
    for (size_t i = 0; i < buf.size(); ++i)
    {
        if (i % 16 == 0) std::cout << "  ";
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(buf[i]) << ' ';
        if (i % 16 == 15) std::cout << '\n';
    }
    if (buf.size() % 16 != 0) std::cout << '\n';
    std::cout << std::dec;
}

} // namespace creds_store

int main()
{
    const std::string user_name = "cs1d";
    const std::string password  = "abc";
    const std::uint8_t key = static_cast<std::uint8_t>('A');

    std::cout << "saving...\n";
    if (!creds_store::save_creds(user_name, password, key))
    {
        std::cout << "save failed\n";
        return 1;
    }

    creds_store::dump_file_hex("key.dat");

    std::uint8_t key_read = 0;
    if (creds_store::get_key_from_file("key.dat", key_read))
        std::cout << "key(read from file tail): " << static_cast<int>(key_read) << "\n";
    else
        std::cout << "get_key_from_file failed\n";

    std::string u2, p2;
    std::cout << "loading...\n";
    if (!creds_store::load_creds(u2, p2))
    {
        std::cout << "load failed\n";
        return 1;
    }

    std::cout << "user_name: " << u2 << "\n";
    std::cout << "password : " << p2 << "\n";

    return 0;
}
