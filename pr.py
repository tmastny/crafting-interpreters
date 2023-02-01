
import os
import requests
import time
from subprocess import run, PIPE

branches = run(["git", "branch"], stdout=PIPE).stdout
branches = [
    branch.strip()
    for branch in branches.decode('utf-8').split("\n")
    if "chapter" in branch
]

headers = {
  "Authorization": f"token {os.getenv('GITHUB_TOKEN')}",
  "Accept": "application/vnd.github+json"
}

url = f"https://api.github.com/repos/tmastny/crafting-interpreters/pulls"

response = requests.get("https://api.github.com/rate_limit", headers=headers)
print(response.text)

last = "start"
wait = True
for branch in branches:
    if branch == "chapter-18":
        wait = False

    if wait:
        continue

    payload = {
      "title": branch,
      "head": branch,
      "base": last,
      "body": ""
    }
    response = requests.post(url, headers=headers, json=payload)

    if response.status_code != 201:
        print(f"Failed: {response.text}")

    last = branch[:branch.find("_")] if "_" in branch else branch
    time.sleep(10)
