import subprocess

subprocess.run(["git", "add", "."], check=True)  #添加缓存
subprocess.run(["git", "commit", "-m", "1.0.063"], check=True)  #提交更改
subprocess.run(["git", "push", "--force"], check=True)  #强制推送代码
