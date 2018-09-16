import pyautogui, clipboard

pyautogui.moveTo(100, 150)
pyautogui.click()
pyautogui.typewrite('Hello world!', interval=0.05)  # type with quarter-second pause in between each key
pyautogui.press('tab')
pyautogui.typewrite('Hello,wolf,test', interval=0.05)  # type with quarter-second pause in between each key
pyautogui.press('tab')
pyautogui.press('tab')
pyautogui.press('enter')
pyautogui.hotkey('shift','tab')
pyautogui.hotkey('ctrl','a')
pyautogui.hotkey('ctrl','c')

text = clipboard.paste() 
print(text.strip() == "Hello")