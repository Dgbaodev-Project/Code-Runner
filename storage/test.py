import websocket
import threading
import time

def on_message(ws, message):
    print(f"Nhận được tin nhắn: {message}")

def on_error(ws, error):
    print(f"Lỗi: {error}")

def on_close(ws, close_status_code, close_msg):
    print("Kết nối WebSocket đã đóng")

def on_open(ws):
    print("Kết nối WebSocket đã được mở")
    def run():
        for i in range(3):
            time.sleep(1)
            message = f"Tin nhắn {i+1} từ client"
            ws.send(message)
            print(f"Đã gửi tin nhắn: {message}")
        time.sleep(1)
        ws.close()
    threading.Thread(target=run).start()

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws_url = "ws://test12341234.freesites.eu.org/"

    ws = websocket.WebSocketApp(ws_url,
                                on_open=on_open,
                                on_message=on_message,
                                on_error=on_error,
                                on_close=on_close)

    ws.run_forever()
