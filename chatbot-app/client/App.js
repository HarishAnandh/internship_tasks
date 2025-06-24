import React, { useState, useEffect } from "react";
import { io } from "socket.io-client";

const socket = io("http://localhost:5000");

function App() {
  const [message, setMessage] = useState("");
  const [chat, setChat] = useState([]);

  const sendMessage = () => {
    if (message.trim()) {
      const newMsg = { text: message, time: new Date().toLocaleTimeString() };
      socket.emit("send_message", newMsg);
      setMessage("");
    }
  };

  useEffect(() => {
    socket.on("receive_message", (data) => {
      setChat((prev) => [...prev, data]);
    });

    return () => socket.disconnect();
  }, []);

  return (
    <div style={{ padding: 20 }}>
      <h2>💬 Real-Time Chat</h2>
      <div style={{ height: 200, overflowY: "scroll", border: "1px solid #ccc", padding: 10 }}>
        {chat.map((msg, i) => (
          <div key={i}><strong>{msg.time}</strong>: {msg.text}</div>
        ))}
      </div>
      <input
        value={message}
        onChange={(e) => setMessage(e.target.value)}
        placeholder="Type message"
        style={{ marginTop: 10, padding: 5 }}
      />
      <button onClick={sendMessage} style={{ marginLeft: 10 }}>
        Send
      </button>
    </div>
  );
}

export default App;
