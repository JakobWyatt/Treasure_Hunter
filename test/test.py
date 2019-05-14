import subprocess
import os

def test_suite():
    build()
    os.remove("../src/adventure.log")

def build():
    subprocess.call(["make", "clean"], cwd="../src")
    subprocess.call(["make"], cwd="../src")

if __name__ == "__main__":
    test_suite()
