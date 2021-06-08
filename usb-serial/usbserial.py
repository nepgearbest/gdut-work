import serial
import threading
import time
import serial.tools.list_ports


# 本次作业每次接受144个字节
class usb_serial:
    def __init__(self, com="COM7", bps=115200, timeout=0.5):
        self.ser_property = None
        self.wait_end = None
        self.alive = False
        self.thread_read = None

        self.COM = com
        self.BPS = bps
        self.Timeout = timeout
        self.port_lsit = list(serial.tools.list_ports.comports())
        if len(self.port_lsit) == 0:
            print("Could Not Find Any COM")
        else:
            self.engine = serial.Serial(self.COM, self.BPS, timeout=self.Timeout)

    def waiting(self):
        if not self.wait_end is None:
            self.wait_end.wait()

    def setStopEvent(self):
        if not self.wait_end is None:
            self.wait_end.set()
            self.alive = False
            self.stop()

    def start(self):
        if self.engine.isOpen():
            print("打开串口成功")
            self.wait_end = threading.Event()
            self.alive = True
            self.thread_read = threading.Thread(target=self.FirstReader)
            self.thread_read.setDaemon(False)  # 6.7 update:这东西必须得设置为False，不然会程序跑完自己就结束了
            self.thread_read.start()
        else:
            print("打开失败")

    def FirstReader(self):
        while self.alive:
            time.sleep(0.5)

            data = ""
            data = data.encode('utf-8')
            n = self.engine.in_waiting

            if n:
                print("in reading,len=%d" % (n))
                data = data + self.engine.read(n)
                print('rec:', data)
                # TODO: 请增加文件存取

    def stop(self):
        self.alive = False
        self.thread_read.join()
        if self.engine.isOpen():
            self.engine.close()

    def SendDate(self, send):
        self.engine.write(send)


a = usb_serial(com="COM7")
a.start()
print(a.thread_read.is_alive)
