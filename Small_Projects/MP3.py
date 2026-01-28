#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import argparse
from typing import List, Tuple
from mutagen.id3 import ID3, ID3NoHeaderError, SYLT, USLT, Encoding
from mutagen.mp3 import MP3

def read_text_auto(path: str) -> str:
    encodings = ["utf-8-sig", "utf-8", "gbk", "gb2312", "big5", "shift_jis", "cp936", "latin-1"]
    last_err = None
    for enc in encodings:
        try:
            with open(path, "r", encoding=enc) as f:
                return f.read()
        except Exception as e:
            last_err = e
    raise last_err if last_err else RuntimeError(f"无法读取文件: {path}")

_ts_re = re.compile(r"\[(\d{1,2}):(\d{1,2})(?:[.:](\d{1,3}))?\]")

def parse_lrc(lrc_text: str) -> List[Tuple[int, str]]:
    """
    把 LRC 解析成 [(time_ms, lyric), ...]
    """
    events: List[Tuple[int, str]] = []
    for raw_line in lrc_text.splitlines():
        line = raw_line.strip()
        if not line:
            continue
        matches = list(_ts_re.finditer(line))
        if not matches:
            continue
        lyric = _ts_re.sub("", line).strip()
        if lyric == "":
            continue
        for m in matches:
            mm = int(m.group(1))
            ss = int(m.group(2))
            ms = m.group(3) or "0"
            ms = (ms + "000")[:3]
            t_ms = (mm * 60 + ss) * 1000 + int(ms)
            events.append((t_ms, lyric))
    events.sort(key=lambda x: x[0])
    return events

def strip_timestamps(lrc_text: str) -> str:
    out_lines = []
    for raw_line in lrc_text.splitlines():
        line = _ts_re.sub("", raw_line).strip()
        if line:
            out_lines.append(line)
    return "\n".join(out_lines).strip()

def remove_lyrics_frames(tags: ID3):
    for k in list(tags.keys()):
        if k.startswith("SYLT") or k.startswith("USLT"):
            del tags[k]

def write_sylt(mp3_path: str, events: List[Tuple[int, str]], lang: str, desc: str):
    try:
        tags = ID3(mp3_path)
    except ID3NoHeaderError:
        tags = ID3()
    remove_lyrics_frames(tags)

    # 修复：SYLT 需要 [(text, time_ms)]，不是反的
    pairs = [(lyric, t_ms) for (t_ms, lyric) in events]

    sylt = SYLT(
        encoding=3,   # UTF-8
        lang=lang,
        format=2,     # 毫秒
        type=1,       # 歌词
        desc=desc,
        text=pairs
    )
    tags.add(sylt)
    tags.save(mp3_path, v2_version=3)

def write_uslt(mp3_path: str, text: str, lang: str, desc: str):
    try:
        tags = ID3(mp3_path)
    except ID3NoHeaderError:
        tags = ID3()
    remove_lyrics_frames(tags)
    uslt = USLT(encoding=3, lang=lang, desc=desc, text=text)
    tags.add(uslt)
    tags.save(mp3_path, v2_version=3)

def main():
    parser = argparse.ArgumentParser(description="批量给 MP3 文件嵌入 LRC 歌词 (SYLT 或 USLT)")
    parser.add_argument("--root", default=".", help="包含 MP3 的目录，默认当前目录")
    parser.add_argument("--lyric-dir", default="Lyric", help="歌词子目录名，默认 Lyric")
    parser.add_argument("--mode", choices=["sylt", "uslt"], default="sylt", help="写入 SYLT(带时间) 或 USLT(纯文本)")
    parser.add_argument("--lang", default="eng", help="语言码(ISO-639-2)，中文用 zho，默认 eng")
    parser.add_argument("--desc", default="embedded by script", help="歌词描述字段")
    args = parser.parse_args()

    root = os.path.abspath(args.root)
    lrc_dir = os.path.join(root, args.lyric_dir)

    if not os.path.isdir(root):
        print(f"[X] 目录不存在: {root}")
        return
    if not os.path.isdir(lrc_dir):
        print(f"[X] 歌词目录不存在: {lrc_dir}")
        return

    mp3s = [f for f in os.listdir(root) if f.lower().endswith(".mp3")]
    if not mp3s:
        print("[!] 该目录下没有 mp3 文件。")
        return

    ok, skip, fail = 0, 0, 0

    for fn in mp3s:
        base = os.path.splitext(fn)[0]
        lrc_path = os.path.join(lrc_dir, base + ".lrc")
        mp3_path = os.path.join(root, fn)

        if not os.path.isfile(lrc_path):
            print(f"[-] 缺歌词文件: {fn}")
            skip += 1
            continue

        try:
            lrc_text = read_text_auto(lrc_path)
            if args.mode == "sylt":
                events = parse_lrc(lrc_text)
                if not events:
                    print(f"[!] {base}.lrc 没有解析出时间戳，用 USLT 方式代替。")
                    write_uslt(mp3_path, strip_timestamps(lrc_text), args.lang, args.desc)
                else:
                    write_sylt(mp3_path, events, args.lang, args.desc)
            else:
                write_uslt(mp3_path, strip_timestamps(lrc_text), args.lang, args.desc)

            _ = MP3(mp3_path)  # 检查文件
            print(f"[✓] 写入成功: {fn}")
            ok += 1
        except Exception as e:
            print(f"[X] 写入失败 {fn}: {e}")
            fail += 1

    print(f"\n完成。成功 {ok}，跳过 {skip}，失败 {fail}。")

if __name__ == "__main__":
    main()
