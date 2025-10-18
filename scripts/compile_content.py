#!/usr/bin/env python3
"""
Generate content.tex from existing topics and problems
- Only includes non-empty .tex files
- Folder numbering is ignored in titles
- Leaves main.tex untouched
- Problems section is appended at the end
- Includes 'intro.tex' for both sections and subsections only if folder contains any non-empty .tex
"""

import os, re

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
TOPICS_DIR = os.path.join(ROOT, "topics")
PROB_DIR = os.path.join(ROOT, "problems")
CONTENT_FILE = os.path.join(ROOT, "content.tex")

def slug_to_title(name):
    name = re.sub(r"^\d+(?:_\d+)?_", "", name)  # remove leading "1_" or "1_2_"
    name = re.sub(r"\.tex$", "", name)          # remove .tex
    return name.replace("_", " ").title()

def is_nonempty_tex(path):
    try:
        if not os.path.isfile(path) or not path.endswith(".tex"):
            return False
        with open(path, "r", encoding="utf-8-sig") as f:
            content = f.read().strip()
        return len(content) > 1
    except Exception:
        return False

def has_nonempty_tex_in_folder(folder):
    if not os.path.exists(folder):
        return False
    for f in os.listdir(folder):
        if f.endswith(".tex") and is_nonempty_tex(os.path.join(folder, f)):
            return True
    return False

def walk_sorted(d):
    for entry in sorted(os.listdir(d)):
        full_path = os.path.join(d, entry)
        if os.path.isdir(full_path):
            yield entry, full_path

def generate_content():
    with open(CONTENT_FILE, "w", encoding="utf-8") as f:
        if os.path.exists(TOPICS_DIR):
            for cat_name, cat_path in walk_sorted(TOPICS_DIR):
                # Skip empty category
                if not has_nonempty_tex_in_folder(cat_path) and not any(has_nonempty_tex_in_folder(os.path.join(cat_path, sub)) for sub, _ in walk_sorted(cat_path)):
                    continue
                cat_written = False

                section_intro_file = os.path.join(cat_path, "intro.tex")
                if is_nonempty_tex(section_intro_file):
                    f.write(f"\\section{{{slug_to_title(cat_name)}}}\n")
                    cat_written = True
                    rel = os.path.relpath(section_intro_file, ROOT)
                    f.write(f"\\input{{{rel}}}\n\n")

                for sub_name, sub_path in walk_sorted(cat_path):
                    # Skip empty subcategory
                    if not has_nonempty_tex_in_folder(sub_path):
                        continue
                    sub_written = False

                    if not cat_written:
                        f.write(f"\\section{{{slug_to_title(cat_name)}}}\n")
                        cat_written = True
                    f.write(f"\\subsection{{{slug_to_title(sub_name)}}}\n")

                    subsection_intro_file = os.path.join(sub_path, "intro.tex")
                    if is_nonempty_tex(subsection_intro_file):
                        rel = os.path.relpath(subsection_intro_file, ROOT)
                        f.write(f"\\input{{{rel}}}\n\n")
                        sub_written = True

                    topic_files = sorted([os.path.join(sub_path, t)
                                          for t in os.listdir(sub_path)
                                          if t.endswith(".tex") and t != "intro.tex" and is_nonempty_tex(os.path.join(sub_path, t))])
                    for t in topic_files:
                        title = slug_to_title(os.path.splitext(os.path.basename(t))[0])
                        rel = os.path.relpath(t, ROOT)
                        f.write(f"\\subsubsection{{{title}}}\n\\input{{{rel}}}\n")
                    f.write("\\newpage\n")

        # --- Problems section appended at the end ---
        f.write("\n\\appendix\n\\section{Problems}\n")
        if os.path.exists(PROB_DIR):
            for cat_name, cat_path in walk_sorted(PROB_DIR):
                cat_written = False
                for sub_name, sub_path in walk_sorted(cat_path):
                    sub_written = False
                    for topic_name, topic_path in walk_sorted(sub_path):
                        topic_written = False
                        for prob_file in sorted(os.listdir(topic_path)):
                            prob_path = os.path.join(topic_path, prob_file)
                            if prob_path.endswith(".tex") and is_nonempty_tex(prob_path):
                                if not cat_written:
                                    f.write(f"\\section{{{slug_to_title(cat_name)}}}\n")
                                    cat_written = True
                                if not sub_written:
                                    f.write(f"\\subsection{{{slug_to_title(sub_name)}}}\n")
                                    sub_written = True
                                if not topic_written:
                                    f.write(f"\\subsubsection{{{slug_to_title(topic_name)}}}\n")
                                    topic_written = True
                                prob_title = slug_to_title(os.path.splitext(os.path.basename(prob_path))[0])
                                rel = os.path.relpath(prob_path, ROOT)
                                f.write(f"\\paragraph{{{prob_title}}}\n\\input{{{rel}}}\n\n")

if __name__ == "__main__":
    generate_content()
    print("✅ content.tex generated with problems at the end")