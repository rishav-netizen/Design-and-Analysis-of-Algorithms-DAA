from pathlib import Path

# Base directory (LAB1)
base_dir = Path(__file__).parent

# Create folders for each question
for i in range(1, 7):
    question_dir = base_dir / f"Q{i}"
    question_dir.mkdir(exist_ok=True)

    # Optional starter files
    (question_dir / "main.c").touch(exist_ok=True)
    (question_dir / "README.md").touch(exist_ok=True)

print("✅ Successfully created folders for Q1 to Q6.")