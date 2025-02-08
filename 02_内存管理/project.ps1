git config --global user.name "yangmeia"
git config --global user.email "1763055882@qq.com"
git config --global http.sslverify false

git init 		#初始化git仓库
git add C:\share\006_C++\c++_note\02_内存管理 		#添加所有文件到暂存区
git commit -m "first commit"	#提交到本地仓库

# git checkout -b master    # 创建并切换到新的分支（例如 main）
git branch -M master		#将主分支切换为分支master
git remote add origin https://github.com/yangmeia/project.git	#添加远程仓库
git push -u origin master	#推送到远程仓库