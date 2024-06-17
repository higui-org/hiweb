import requests
from bs4 import BeautifulSoup
from collections import Counter


with open("resources.txt", "r") as f:
    urls = [line.strip() for line in f.readlines()]

# Find popular tags
popular_tags = [
    "div", "form", "input",
    "br", "hr", "ul", "li",
    "span", "a", 
    "h1", "h2", "h3", "h4", "h5", "h6",
    "script", "style", "section", "button",
    "strong"]

def parse_tags(urls):
    tag_counter = Counter()
    for url in urls:
        response = requests.get(url)
        soup = BeautifulSoup(response.content, "html.parser")
        tags = [tag.name for tag in soup.find_all()]
        tag_counter.update(tags)
    return tag_counter

# Parse tag stats
tag_stats = parse_tags(urls)

# Filter tags
common_tags = {tag: count for tag, count in tag_stats.items() if tag in popular_tags}
other_tags = {tag: count for tag, count in tag_stats.items() if tag not in popular_tags}

# Show results
print("Common tags:")
for tag, count in common_tags.items():
    print(f"tag '{tag}': {count}")

# Write results
with open("common_tags.txt", "w") as common_file:
    for tag, count in common_tags.items():
        common_file.write(f"tag '{tag}': {count}\n")

with open("other_tags.txt", "w") as other_file:
    for tag, count in other_tags.items():
        other_file.write(f"tag '{tag}': {count}\n")