from pywinauto import Desktop, Application

Application().start("D:\\project\\Sem5\\QualityManagementSoftware\\lab5\\ahocorasick\\ahocorasick.exe")

# connect to another process spawned by explorer.exe
# Note: make sure the script is running as Administrator!
app = Application(backend="uia").connect(path="ahocorasick.exe", title="Aho")
