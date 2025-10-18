#!/usr/bin/env python3
"""
Generate folders and empty topic .tex files
- Does NOT touch main.tex or content.tex
- Only creates folders and files if they don't exist
- Creates intro.tex in each section and subsection
"""

import os, re, json

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
TOPICS_DIR = os.path.join(ROOT, "topics")
JSON_FILE = os.path.join(ROOT, "src/topicList.json")
PROB_DIR = os.path.join(ROOT, "problems")

def slugify(s):
    return re.sub(r"[^a-zA-Z0-9_-]+", "_", s.strip().lower()).strip("_")

def ensure_dir(path):
    os.makedirs(path, exist_ok=True)

def ensure_file(path, content=""):
    if not os.path.exists(path):
        with open(path, "w", encoding="utf-8") as f:
            f.write(content)

def load_topiclist():
    if not os.path.exists(JSON_FILE):
        print("❌ topicList.json not found")
        return []
    with open(JSON_FILE, encoding="utf-8") as f:
        return json.load(f)

def create_folders(topic_list):
    for cat_idx, cat in enumerate(topic_list, 1):
        cat_dir = os.path.join(TOPICS_DIR, f"{cat_idx:02d}_{slugify(cat['category_title'])}")
        prob_dir = os.path.join(PROB_DIR, f"{cat_idx:02d}_{slugify(cat['category_title'])}")
        ensure_dir(prob_dir)
        ensure_dir(cat_dir)

        # Create intro.tex for the section if not exists
        ensure_file(os.path.join(cat_dir, "intro.tex"), " ")

        for sub_idx, sub in enumerate(cat.get("sub_categories", []), 1):
            sub_dir = os.path.join(cat_dir, f"{sub_idx:02d}_{slugify(sub['sub_category_title'])}")
            prob_sub_dir = os.path.join(prob_dir, f"{sub_idx:02d}_{slugify(sub['sub_category_title'])}")

            ensure_dir(sub_dir)
            ensure_dir(prob_sub_dir)

            # Create intro.tex for the subsection if not exists
            ensure_file(os.path.join(sub_dir, "intro.tex"), " ")

            for t in sub.get("topics", []):
                topic_title = t["topic_title"]
                topic_slug = str(4-t["importance"])+ "_" + str(t["difficulty"]) + "_" +slugify(topic_title)
                fname = os.path.join(sub_dir, topic_slug + ".tex")
                prob_topic_dir = os.path.join(prob_sub_dir, topic_slug)

                ensure_dir(prob_topic_dir)
                ensure_file(fname, f" ")

if __name__ == "__main__":
    topic_list = load_topiclist()
    if not topic_list:
        exit(1)
    create_folders(topic_list)
    print("✅ Folder structure, intro.tex, and empty topic files created.")