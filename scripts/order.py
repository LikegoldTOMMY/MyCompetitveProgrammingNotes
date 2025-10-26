#!/usr/bin/env python3

import os, re, json, shutil
import difflib

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
PRACTICE_DIR = os.path.join(ROOT, "Practice")
TOPICS_DIR = os.path.join(ROOT, "topics")
PROB_DIR = os.path.join(ROOT, "problems")
JSON_FILE = os.path.join(ROOT, "src/topicList.json")

def slugify(s):
    return re.sub(r"[^a-zA-Z0-9_-]+", "_", s.strip().lower()).strip("_")

def load_topiclist():
    with open(JSON_FILE, encoding="utf-8") as f:
        return json.load(f)

def find_topic_path(topic_list, topic_query):
    q = topic_query.lower().strip()
    # Build a list of all topics with their indices for fuzzy matching
    all_topics = []
    for i, cat in enumerate(topic_list):
        for j, sub in enumerate(cat.get("sub_categories", [])):
            for t in sub.get("topics", []):
                all_topics.append((i, j, t))
    # Extract topic titles for matching
    topic_titles = [t["topic_title"].lower() for _, _, t in all_topics]
    matches = difflib.get_close_matches(q, topic_titles, n=1, cutoff=0.75)
    if matches:
        matched_title = matches[0]
        for i, j, t in all_topics:
            if t["topic_title"].lower() == matched_title:
                topic_slug = str(4 - t["importance"]) + "_" + str(t["difficulty"]) + "_" + slugify(t["topic_title"])
                dest_dir = os.path.join(
                    PROB_DIR,
                    f"{i+1:02d}_{slugify(topic_list[i]['category_title'])}",
                    f"{j+1:02d}_{slugify(topic_list[i]['sub_categories'][j]['sub_category_title'])}",
                    topic_slug
                )
                return dest_dir
    return None

def process_practice_files():
    topic_list = load_topiclist()
    for root, _, files in os.walk(PRACTICE_DIR):
        for file in files:
            if file.endswith(".cpp"):
                file_path = os.path.join(root, file)
                with open(file_path, encoding="utf-8") as f:
                    first_line = f.readline().strip()
                match = re.match(r"//\s*Topic:\s*(.+)", first_line)
                if not match:
                    print(f"❌ No topic found in {file}")
                    continue
                topic_name = match.group(1).strip()
                dest_dir = find_topic_path(topic_list, topic_name)
                if dest_dir:
                    os.makedirs(dest_dir, exist_ok=True)
                    dest_path = os.path.join(dest_dir, file)
                    shutil.move(file_path, dest_path)
                    print(f"✅ Moved {file} → {dest_dir}")
                else:
                    print(f"⚠️ Topic '{topic_name}' not found for {file}")

if __name__ == "__main__":
    process_practice_files()