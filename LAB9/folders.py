from pathlib import Path

initialQuestion = 1
finalQuestion = 10

baseDirectory = Path(__file__).parent

for i in range(initialQuestion, finalQuestion):
    file = baseDirectory / f"Q{i}"
    file.mkdir(exist_ok=True)
    (file / "main.c").touch(exist_ok=True)
    (file / "README.md").touch(exist_ok=True)