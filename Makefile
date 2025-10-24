PYTHON = python3
MAIN = main.tex
PDF = main.pdf

all: 
	$(PYTHON) scripts/generate_topics.py
	$(PYTHON) scripts/compile_content.py

topic_list:
	$(PYTHON) scripts/generate_topics.py

# Generate content.tex
content:
	$(PYTHON) scripts/compile_content.py

topic:
	$(PYTHON) scripts/create_topic.py

clean:
	find . -type f \( -name "*.aux" -o -name "*.log" -o -name "*.toc" -o -name "*.out" -o -name "*.bbl" -o -name "*.blg" -o -name "*.synctex.gz" \) -exec rm -f {} +