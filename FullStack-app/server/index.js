const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcryptjs');

const app = express();
const PORT = 5000;
const JWT_SECRET = "your_jwt_secret";

app.use(cors());
app.use(express.json());

mongoose.connect("mongodb://localhost:27017/fullstack-auth", {
    useNewUrlParser: true,
    useUnifiedTopology: true
});

// User Schema
const User = mongoose.model("User", new mongoose.Schema({
    name: String,
    email: { type: String, unique: true },
    password: String
}));

// Register
app.post("/register", async (req, res) => {
    const { name, email, password } = req.body;
    const hashedPassword = await bcrypt.hash(password, 10);

    try {
        await User.create({ name, email, password: hashedPassword });
        res.status(200).json({ message: "User created" });
    } catch (e) {
        res.status(400).json({ error: "User already exists" });
    }
});

// Login
app.post("/login", async (req, res) => {
    const { email, password } = req.body;
    const user = await User.findOne({ email });
    if (!user) return res.status(401).json({ error: "Invalid email" });

    const isPasswordValid = await bcrypt.compare(password, user.password);
    if (!isPasswordValid) return res.status(401).json({ error: "Invalid password" });

    const token = jwt.sign({ id: user._id }, JWT_SECRET);
    res.json({ token });
});

app.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`));
