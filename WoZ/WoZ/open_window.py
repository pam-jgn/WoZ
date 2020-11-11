
import os, sys, time, datetime
import locale
import tkinter as tk
from tkinter import ttk
import threading
from PIL import Image, ImageTk
import requests


files = ["C:/Users/buffa/source/repos/WoZ/WoZ/evalution.txt"]
#files = ["evalution.txt"]
locale.setlocale(locale.LC_CTYPE, "Japanese_Japan.932")


def read_Files(Files):
  data = []
  for file in Files:
    with open(file) as f:
      s = f.read()
      # 分割
      lines=s.split('\n')
      data.extend(lines)
  return data


def send_line_notify(notification_message):
    """
    LINEに通知する
    """
    line_notify_token = 'ijcQXcyIjPuh2l0eLuAOz3DPbhMpTrrkydIzA4st1NY'
    line_notify_api = 'https://notify-api.line.me/api/notify'
    headers = {'Authorization': f'Bearer {line_notify_token}'}
    #data = {'message': f'message: {notification_message}'}
    data = {'message': notification_message}
    proxies = {'http':'http://proxy.nagaokaut.ac.jp:8080', 'https':'https://proxy.nagaokaut.ac.jp:8080'}
   ## requests.post(line_notify_api, headers = headers, data = data, proxies = proxies)
    requests.post(line_notify_api, headers = headers, data = data)


class Win1(tk.Frame):
    def __init__(self,master):
        super().__init__(master)
        self.pack()
        self.master.geometry('700x730')
        self.master.title('消費電力状況')
        self.create_widgets()

    def create_widgets(self):
        dt_now = datetime.datetime.now()
        self.label_date = ttk.Label(self)
        self.label_date.configure(text=str(dt_now.strftime('%Y年%m月%d日 %H:%M:%S')),foreground = 'red', font=(u'ＭＳ ゴシック', 20))
        self.label_date.pack()


        load = Image.open("間取り.png")
        load = load.resize((520,450),Image.ANTIALIAS)
        render = ImageTk.PhotoImage(load)
        self.img = ttk.Label(self)
        self.img.configure(image=render)
        self.img.image = render
        self.img.pack()

        datas = read_Files(files)
        for message in datas:
            self.message = ttk.Label(self)
            self.message.configure(text=message, font=(u'ＭＳ ゴシック', 20))
            self.message.pack()

        self.button_new_win = ttk.Button(self)
        self.button_new_win.configure(text="評価ウィンドウ表示", command = self.new_window)
        self.button_new_win.pack()

    #Call back function
    def new_window(self):
        self.newWindow = tk.Toplevel(self.master)
        self.app = Win2(self.newWindow)



class Win2(tk.Frame):
    def __init__(self,master):

        super().__init__(master)
        self.pack()
        self.master.geometry("300x700")
        self.master.title("結果送信")
        self.create_widgets()

    def create_widgets(self):
     #   self.txt = tk.Text(self)
     #   self.txt.configure(height=10)
     #   self.txt.pack()

        self.label_space = ttk.Label(self, text="")
        self.label_space.pack(pady = 10)
        self.label = ttk.Label(self, text="止める機器")
        self.label.pack()
        dict= {'PC①':["室内、ゾーン外、ON(B)", "室外、ON(D)"], 'PC②':["室内、ゾーン外、ON(B)", "室外、ON(D)"], 'PC③':["室内、ゾーン外、ON(B)", "室外、ON(D)"], 'PC④':["室内、ゾーン外、ON(B)", "室外、ON(D)"], 'PC⑤':["室内、ゾーン外、ON(B)", "室外、ON(D)"], 'プリンタ':["使われなかった", "使用回数が少ない", "使用者が少ない"], 'ケトル':["使われなかった", "使用回数が少ない", "使用者が少ない", "電気ストーブと併用できない"], '冷蔵庫':["使われなかった", "使用回数が少ない", "使用者が少ない"], '電子レンジ':["使われなかった", "使用回数が少ない", "使用者が少ない"], '電気ストーブ':["電力消費が多い", "ケトルと併用できない"]}
        var_material = tk.StringVar()
        self.cmbox1 = ttk.Combobox(self, values=list(dict.keys()), textvariable=var_material)

        self.cmbox2 = ttk.Combobox(self)

        self.cmbox1.bind('<<ComboboxSelected>>', lambda event:self.cmbox2.config(values=dict[var_material.get()]))
        self.cmbox1.pack()

        self.label_space = ttk.Label(self, text="")
        self.label_space.pack(pady = 10)
        self.label = ttk.Label(self, text="理由")
        self.label.pack()

        self.cmbox2.bind('<<ComboboxSelected>>', self.show_option)
        self.cmbox2.pack()


    def quit_window(self):
      #  text_check = self.listbox.curselection()[0]
      #  self.txt.insert('1.0', self.listbox.get(text_check))

      #  line_message = self.txt.get("1.0", "end")
      send_person = self.var.get()
      send_person_message = send_person + "君へのメッセージです。\n"
      send_line_notify(send_person_message)

      stop_device = self.cmbox1.get()
      stop_device_message = stop_device + "の電源を切ってください\n"
      reason = self.cmbox2.get()
      reason_message = ""
      if reason == "室内、ゾーン外、ON(B)":
          reason_message = "理由：" + stop_device + "の使用者はPCをあまり使用していないからです。\n"
      elif reason == "室外、ON(D)":
          reason_message = "理由：" + stop_device + "の使用者は室内にいないことが多いからです。\n"
      elif reason == "使われなかった":
          reason_message = "理由："+ stop_device + "は一度も使用されていないからです。\n"
      elif reason == "使用回数が少ない":
          reason_message = "理由：" + stop_device + "は使用された回数が少ないからです。\n"
      elif reason == "使用者が少ない":
          reason_message = "理由：" + stop_device + "を使用した人が少なかったからです。\n"
      elif reason == "電気ストーブと併用できない" or reason == "ケトルと併用できない":
          reason_message = "理由：ケトルをと電気ストーブを併用すると、停電の恐れがあるからです。\n"

      if stop_device == "PC①" or stop_device == "PC②" or stop_device == "PC③" or stop_device == "PC④" or stop_device == "PC⑤":
          rouhi_wat = self.rouhi_spin.get()
          rouhi_message = "（%s[W]浪費しています）" %(rouhi_wat)
          line_message = stop_device_message + reason_message + rouhi_message
      elif stop_device == "プリンタ" or stop_device == "ケトル" or stop_device == "冷蔵庫" or stop_device == "電子レンジ":
          if reason == "使用回数が少ない":
              use_num = self.use_num_spin.get()
              use_num_message = "(使用回数は%s回)" %(use_num)
              line_message = stop_device_message + reason_message + use_num_message
          elif reason == "使用者が少ない":
              usr_num = self.usr_num_spin.get()
              usr_num_message = "(使用者は%s人)" %(usr_num)
              line_message = stop_device_message + reason_message + usr_num_message
          else:
              line_message = stop_device_message + reason_message
      elif stop_device == "電気ストーブ":
          if reason == "電力消費が多い":
              line_message = "電気ストーブ"+ self.Elstove_cmbox.get() + "の電源を切ってください\n" + "理由:電気ストーブだけで" + self.Elstove_spin.get() + "[W]電力を消費しているからです\n"
          if reason == "ケトルと併用できない":
              line_message = "電気ストーブ"+ self.Elstove_cmbox.get() + "の電源を切ってください\n" + reason_message
      print(line_message + "\n")
      send_line_notify(line_message)

      self.master.destroy()

    def show_option(self, event):
        stop_device = self.cmbox1.get()
        if stop_device == "PC①" or stop_device == "PC②" or stop_device == "PC③" or stop_device == "PC④" or stop_device == "PC⑤":
            self.label_space = ttk.Label(self, text="")
            self.label_space.pack(pady = 10)
            self.label = ttk.Label(self, text="浪費電力")
            self.label.pack()
            self.rouhi_spin = ttk.Spinbox(self, from_ = 0, to = 1000, increment = 1, width = 10)
            self.rouhi_spin.pack()
        elif stop_device == "ケトル" or stop_device == "プリンタ" or stop_device == "冷蔵庫" or stop_device == "電子レンジ":
            if self.cmbox2.get() == "使用回数が少ない":
                self.label_space = ttk.Label(self, text="")
                self.label_space.pack(pady = 10)
                self.label = ttk.Label(self, text="使用回数")
                self.label.pack()
                self.use_num_spin = ttk.Spinbox(self, from_ = 0, to = 1000, increment = 1, width = 10)
                self.use_num_spin.pack()
            elif self.cmbox2.get() == "使用者が少ない":
                self.label_space = ttk.Label(self, text="")
                self.label_space.pack(pady = 10)
                self.label = ttk.Label(self, text="使用者数")
                self.label.pack()
                self.usr_num_spin = ttk.Spinbox(self, from_ = 0, to = 1000, increment = 1, width = 10)
                self.usr_num_spin.pack()
        elif stop_device == "電気ストーブ":
            self.label_space = ttk.Label(self, text="")
            self.label_space.pack(pady = 10)
            self.label = ttk.Label(self, text="止める電気ストーブ")
            self.label.pack()
            self.Elstove_cmbox = ttk.Combobox(self, values = ["①", "②", "③"])
            self.Elstove_cmbox.pack()
            if self.cmbox2.get() == "電力消費が多い":   
                self.label_space = ttk.Label(self, text="")
                self.label_space.pack(pady = 10)
                self.label = ttk.Label(self, text="消費電力")
                self.label.pack()
                self.Elstove_spin = ttk.Spinbox(self, from_ = 0, to = 10000, increment = 1, width = 10)
                self.Elstove_spin.pack()



        self.label_space = ttk.Label(self, text="")
        self.label_space.pack(pady = 10)
        self.label = ttk.Label(self, text="送信相手")
        self.label.pack()
        
        self.var = tk.StringVar(self, value = "V")
        self.rdo = ttk.Radiobutton(self, text = "V", value = "V", var=self.var)
        self.rdo.pack()
        self.rdo = ttk.Radiobutton(self, text = "W", value = "W", var=self.var)
        self.rdo.pack()
        self.rdo = ttk.Radiobutton(self, text = "X", value = "X", var=self.var)
        self.rdo.pack()
        self.rdo = ttk.Radiobutton(self, text = "Y", value = "Y", var=self.var)
        self.rdo.pack()
        self.rdo = ttk.Radiobutton(self, text = "Z", value = "Z", var=self.var)
        self.rdo.pack()

        self.button_quit = ttk.Button(self)
        self.button_quit.configure(text="送信")
        self.button_quit.configure(command=self.quit_window)
        self.button_quit.pack()

def main():
    root = tk.Tk()
    app = Win1(master=root)
    app.mainloop()

# ---  main --#
if __name__ == "__main__": 
    main()