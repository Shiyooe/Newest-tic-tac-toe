
* {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Arial', sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        }

        .container {
            text-align: center;
            background: white;
            padding: 40px;
            border-radius: 20px;
            box-shadow: 0 20px 60px rgba(0,0,0,0.3);
            max-width: 500px;
        }

        h1 {
            color: #333;
            margin-bottom: 20px;
            font-size: 2.5em;
        }

        .mode-selector {
            display: flex;
            gap: 10px;
            justify-content: center;
            margin-bottom: 20px;
        }

        .mode-btn {
            padding: 10px 20px;
            border: 2px solid #667eea;
            background: white;
            color: #667eea;
            border-radius: 10px;
            cursor: pointer;
            font-size: 1em;
            transition: all 0.3s ease;
        }

        .mode-btn:hover {
            background: #f0f0f0;
        }

        .mode-btn.active {
            background: #667eea;
            color: white;
        }

        .difficulty {
            margin-bottom: 20px;
            padding: 15px;
            background: #f0f0f0;
            border-radius: 10px;
        }

        .difficulty label {
            font-weight: bold;
            margin-right: 10px;
        }

        .difficulty select {
            padding: 8px 15px;
            border: 2px solid #667eea;
            border-radius: 5px;
            font-size: 1em;
            cursor: pointer;
        }

        .status {
            font-size: 1.5em;
            margin: 20px 0;
            color: #667eea;
            font-weight: bold;
            min-height: 40px;
        }

        .board {
            display: grid;
            grid-template-columns: repeat(3, 120px);
            grid-gap: 10px;
            margin: 30px auto;
            max-width: 380px;
        }

        .cell {
            width: 120px;
            height: 120px;
            background: #f0f0f0;
            border: none;
            border-radius: 10px;
            font-size: 3em;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s ease;
        }

        .cell:hover:not(:disabled) {
            background: #e0e0e0;
            transform: scale(1.05);
        }

        .cell:disabled {
            cursor: not-allowed;
        }

        .cell.x {
            color: #667eea;
        }

        .cell.o {
            color: #f093fb;
        }

        .cell.winner {
            background: #ffd700;
            animation: pulse 0.5s ease-in-out;
        }

        @keyframes pulse {
            0%, 100% { transform: scale(1); }
            50% { transform: scale(1.1); }
        }

        .reset-btn {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            border: none;
            padding: 15px 40px;
            font-size: 1.2em;
            border-radius: 50px;
            cursor: pointer;
            transition: all 0.3s ease;
            margin-top: 20px;
        }

        .reset-btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 10px 20px rgba(0,0,0,0.2);
        }

        .score {
            display: flex;
            justify-content: space-around;
            margin-top: 30px;
            font-size: 1.2em;
        }

        .score div {
            padding: 10px 20px;
            background: #f0f0f0;
            border-radius: 10px;
        }
