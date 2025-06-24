import React, { useState } from 'react';
import axios from 'axios';

function App() {
  const [isLogin, setIsLogin] = useState(true);
  const [form, setForm] = useState({ name: '', email: '', password: '' });

  const handleChange = (e) => {
    setForm({...form, [e.target.name]: e.target.value});
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const url = isLogin ? 'http://localhost:5000/login' : 'http://localhost:5000/register';
    try {
      const res = await axios.post(url, form);
      alert(isLogin ? `Login success: ${res.data.token}` : res.data.message);
    } catch (err) {
      alert(err.response?.data?.error || "Something went wrong");
    }
  };

  return (
    <div style={{ padding: 30 }}>
      <h2>{isLogin ? "Login" : "Register"}</h2>
      <form onSubmit={handleSubmit}>
        {!isLogin && (
          <input name="name" placeholder="Name" onChange={handleChange} required />
        )}
        <br />
        <input name="email" placeholder="Email" onChange={handleChange} required />
        <br />
        <input type="password" name="password" placeholder="Password" onChange={handleChange} required />
        <br />
        <button type="submit">{isLogin ? "Login" : "Register"}</button>
      </form>
      <button onClick={() => setIsLogin(!isLogin)}>
        {isLogin ? "Go to Register" : "Go to Login"}
      </button>
    </div>
  );
}

export default App;
