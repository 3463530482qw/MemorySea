from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from build_config import build_scene

build_scene(Path(__file__).resolve().parent)
