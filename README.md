# CP Handbook (Template)

This repository is a **template** for your Competitive Programming handbook.
It includes a generator script that scrapes *The Ultimate Topic List* and creates
a full LaTeX skeleton with one `.tex` file per topic. Notes are in English
by default. The compiled PDF will include both notes and problem snippets;
problems are in the appendix of the generated version.

## How to use

1. (Optional) Inspect the repo and example files.
2. Make sure you have Python 3 and a LaTex compiler installed correctly on your machine.
3. (Optional) Run the generator (this uses the json form https://youkn0wwho.academy/topic-list and creates `.tex` topic files)
   ```bash
   make topic_list
   ```
   You can also structure the directories to your liking, but make sure to keep the "problems" and "topics" directories.
4. When you include new files or directories, to compile the content of the file run 
   ```bash
   make content
   ```
   This will create `content.tex` with sections and subsections corresponding to the directory structure, all empty files will be ignored.
5. Compile `main.tex` to get the whole pdf.
6. To remove all latex auxiliary files form the whole directory run 
   ```bash
   make clean
   ```
   

## Notes
- The generated `.tex` files are minimal placeholders; fill them with your notes.
- Problem files should live under `problems/<category>/<topic>/` with `solution.cpp` and `notes.tex`.
- Topic directory structure should be like `topics/<N_category>/<M_subcat>/<I_D_topic.tex>` where N and M are numbers used to order topics and I and D rappresent the importance and difficulty of each topic. Inside each subcategory topics are sorted by importance and than by difficulty.
- In each category or sub-category folder and optional `intro.tex` can be included, and will be rendered before the section or subsection. 
- Problems directory structure should be like `problems/<N_category>/<M_subcat>/<I_D_topic>/` where N,M,I,D are the same as above. Inside each directory multiples `.tex` can be included to rappresent multiple files. Only `.tex` files are included in the final document.


Enjoy!
