import subprocess

subprocess.run(["git.exe", "add", "."], check=True)  # 添加缓存
subprocess.run(["git.exe", "commit", "-m", "0.0.003"], check=True)  # 提交更改
subprocess.run(["git.exe", "push", "origin", "main", "--force"], check=True)  # 强制推送代码
