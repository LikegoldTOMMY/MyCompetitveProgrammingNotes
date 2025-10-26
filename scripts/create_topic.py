#!/usr/bin/env python3


import os, re, json

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
TOPICS_DIR = os.path.join(ROOT, "topics")
JSON_FILE = os.path.join(ROOT, "src/topicList.json")
PROB_DIR = os.path.join(ROOT, "problems")

CYAN = "\033[36m"
YELLOW = "\033[33m"
GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"
BOLD_GREEN = "\033[1;32m"

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


def find_topic_by_name(query, topic_list):
    matches = []
    q = query.lower()
    for cat in topic_list:
        for sub in cat.get("sub_categories", []):
            for t in sub.get("topics", []):
                if q in t["topic_title"].lower():
                    matches.append((cat, sub, t))
    return matches

def fuzzy_select_topic(topic_list, query):
    matches = find_topic_by_name(query, topic_list)
    if not matches:
        print(f"{RED}❌ No matching topics found.{RESET}")
        return None
    print(f"\n📚 Matching topics:\n")
    for i, (cat, sub, t) in enumerate(matches, 1):
        print(f"[{i}] {YELLOW}{cat['category_title']}{RESET} > {YELLOW}{sub['sub_category_title']}{RESET}")
        print(f"    → {GREEN}{t['topic_title']}{RESET}")
    print("\nSelect a topic by number (or enter 0 to cancel):")
    try:
        idx = int(input())
    except:
        print(f"{RED}❌ Invalid input. Please enter a valid number.{RESET}")
        return None
    if idx == 0:
        return None
    try:
        return matches[idx-1]
    except:
        print(f"{RED}❌ Invalid input. Please enter a valid number.{RESET}")
        return None

def create_single_topic(selected, topic_list):
    cat, sub, t = selected
    cat_dir = os.path.join(TOPICS_DIR, f"{topic_list.index(cat)+1:02d}_{slugify(cat['category_title'])}")
    sub_dir = os.path.join(cat_dir, f"{cat['sub_categories'].index(sub)+1:02d}_{slugify(sub['sub_category_title'])}")
    topic_slug = str(4-t["importance"]) + "_" + str(t["difficulty"]) + "_" + slugify(t["topic_title"])
    topic_file = os.path.join(sub_dir, topic_slug + ".tex")
    prob_topic_dir = os.path.join(PROB_DIR, f"{topic_list.index(cat)+1:02d}_{slugify(cat['category_title'])}", f"{cat['sub_categories'].index(sub)+1:02d}_{slugify(sub['sub_category_title'])}", topic_slug)
    ensure_dir(cat_dir)
    ensure_dir(sub_dir)
    ensure_dir(prob_topic_dir)
    ensure_file(os.path.join(cat_dir, "intro.tex"), " ")
    ensure_file(os.path.join(sub_dir, "intro.tex"), " ")
    ensure_file(topic_file, " ")
    os.system('cls' if os.name == 'nt' else 'clear')
    print(f"\n{BOLD_GREEN}✅ Successfully created structure for:{RESET}\n{YELLOW}📁 {cat['category_title']} > {sub['sub_category_title']}{RESET} > {GREEN}{t['topic_title']}{RESET}\n")


if __name__ == "__main__":
    topic_list = load_topiclist()
    if not topic_list:
        exit(1)
    query = ""
    os.system('cls' if os.name == 'nt' else 'clear')

    while(query != "quit"):
        print(f"{CYAN}🔍 Fuzzy topic search{RESET}")
        query = input('Enter topic name ("quit" to exit): ')
        if(query != "quit"):
            selected = fuzzy_select_topic(topic_list,query)
            if selected:
                create_single_topic(selected, topic_list)

    os.system('cls' if os.name == 'nt' else 'clear')
    