from pathlib import Path

lowerLimit: int = 1
upperLimit: int = 4

baseDirectory = Path(__file__).parent

for set_name in ["Set1", "Set2"]:
    set_dir = baseDirectory / set_name
    set_dir.mkdir(exist_ok=True)
    for i in range(lowerLimit, upperLimit + 1):
        q_dir = set_dir / f"Q{i}"
        q_dir.mkdir(exist_ok=True)
        (q_dir / "main.c").touch(exist_ok=True)
        (q_dir / "README.md").touch(exist_ok=True)
