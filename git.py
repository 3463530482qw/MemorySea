import os
import subprocess

# 仓库地址
REPO_URL = "https://github.com/3463530482qw/MemorySea.git"

# 需要忽略的文件和目录（排除 git.py 和 build/）
IGNORE_ITEMS = [".git/", "build/"]

def run_command(command):
    """执行命令行指令并打印输出"""
    print(f"执行命令: {' '.join(command)}")
    result = subprocess.run(command, capture_output=True, text=True)
    if result.stdout:
        print(result.stdout.strip())
    if result.returncode != 0 and result.stderr:
        print(f"提示/错误: {result.stderr.strip()}")
    return result.returncode == 0

def main():
    # 1. 创建 .gitignore 文件
    print(">> 正在生成 .gitignore 文件...")
    with open(".gitignore", "w", encoding="utf-8") as f:
        for item in IGNORE_ITEMS:
            f.write(f"{item}\n")
    print(">> .gitignore 生成完毕！")

    # 2. 初始化 Git 仓库
    if not os.path.exists(".git"):
        run_command(["git", "init"])
    else:
        print(">> Git 仓库已存在，跳过初始化。")

    # 3. 添加文件到暂存区（.gitignore 会自动排除 git.py 和 build/）
    run_command(["git", "add", "."])

    # 4. 提交到本地仓库
    run_command(["git", "commit", "-m", "Initial commit"])

    # 5. 关联远程仓库并推送
    result = subprocess.run(["git", "remote"], capture_output=True, text=True)
    if "origin" not in result.stdout:
        run_command(["git", "remote", "add", "origin", REPO_URL])
    else:
        print(">> 远程仓库 origin 已关联，跳过添加。")

    # 确保主分支名为 main
    run_command(["git", "branch", "-M", "main"])
    
    # 强制推送到 GitHub（覆盖远程仓库的初始文件，如 README 等）
    run_command(["git", "push", "-u", "origin", "main", "--force"])
    print(">> 推送完成！")

if __name__ == "__main__":
    main()
