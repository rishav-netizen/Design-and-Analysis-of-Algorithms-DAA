from pathlib import Path

lowerLimit: int = 1
upperLimit: int = 4

baseDirectory = Path(__file__).parent

for i in range(lowerLimit, upperLimit + 1):
    file = baseDirectory / f"Q{i}"
    file.mkdir(exist_ok=True)
    (file / "main.c").touch(exist_ok=True)
    (file / "README.md").touch(exist_ok=True)
