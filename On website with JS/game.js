
        class TicTacToeGame {
            constructor() {
                this.board = Array(9).fill('');
                this.currentPlayer = 'X';
                this.gameActive = true;
                this.scores = {X: 0, O: 0, draw: 0};
                this.mode = 'pvp';
                this.bot = new TicTacToeBot('medium');
                this.winPatterns = [
                    [0, 1, 2], [3, 4, 5], [6, 7, 8],
                    [0, 3, 6], [1, 4, 7], [2, 5, 8],
                    [0, 4, 8], [2, 4, 6]
                ];
                this.cells = document.querySelectorAll('.cell');
                this.statusText = document.getElementById('status');
                this.initEventListeners();
            }

            initEventListeners() {
                this.cells.forEach(cell => {
                    cell.addEventListener('click', (e) => this.handleCellClick(e));
                });
            }

            handleCellClick(e) {
                const index = parseInt(e.target.dataset.index);
                
                if (this.board[index] !== '' || !this.gameActive) {
                    return;
                }

                this.makeMove(index, this.currentPlayer);

                if (this.gameActive && this.mode === 'bot' && this.currentPlayer === 'O') {
                    setTimeout(() => this.botMove(), 500);
                }
            }

            makeMove(index, player) {
                this.board[index] = player;
                const cell = this.cells[index];
                cell.textContent = player;
                cell.classList.add(player.toLowerCase());
                cell.disabled = true;

                if (this.checkWin()) {
                    this.statusText.textContent = `🎉 ${player} Menang!`;
                    this.gameActive = false;
                    this.scores[player]++;
                    this.updateScores();
                    this.highlightWinner();
                    return;
                }

                if (this.checkDraw()) {
                    this.statusText.textContent = '🤝 Seri!';
                    this.gameActive = false;
                    this.scores.draw++;
                    this.updateScores();
                    return;
                }

                this.currentPlayer = this.currentPlayer === 'X' ? 'O' : 'X';
                const playerName = (this.mode === 'bot' && this.currentPlayer === 'O') ? 'Bot' : this.currentPlayer;
                this.statusText.textContent = `Giliran: ${playerName}`;
            }

            botMove() {
                if (!this.gameActive) return;
                
                const move = this.bot.getMove(this.board, 'O');
                this.makeMove(move, 'O');
            }

            checkWin() {
                return this.winPatterns.some(pattern => {
                    const [a, b, c] = pattern;
                    return this.board[a] && 
                           this.board[a] === this.board[b] && 
                           this.board[a] === this.board[c];
                });
            }

            checkDraw() {
                return this.board.every(cell => cell !== '');
            }

            highlightWinner() {
                this.winPatterns.forEach(pattern => {
                    const [a, b, c] = pattern;
                    if (this.board[a] && 
                        this.board[a] === this.board[b] && 
                        this.board[a] === this.board[c]) {
                        this.cells[a].classList.add('winner');
                        this.cells[b].classList.add('winner');
                        this.cells[c].classList.add('winner');
                    }
                });
            }

            updateScores() {
                document.getElementById('scoreX').textContent = this.scores.X;
                document.getElementById('scoreO').textContent = this.scores.O;
                document.getElementById('scoreDraw').textContent = this.scores.draw;
            }

            setMode(mode) {
                this.mode = mode;
                document.querySelectorAll('.mode-btn').forEach(btn => {
                    btn.classList.remove('active');
                });
                event.target.classList.add('active');
                
                const difficultyDiv = document.getElementById('difficulty');
                difficultyDiv.style.display = mode === 'bot' ? 'block' : 'none';
                
                this.reset();
            }

            setDifficulty(difficulty) {
                this.bot.difficulty = difficulty;
                this.reset();
            }

            reset() {
                this.board = Array(9).fill('');
                this.currentPlayer = 'X';
                this.gameActive = true;
                this.statusText.textContent = 'Giliran: X';
                
                this.cells.forEach(cell => {
                    cell.textContent = '';
                    cell.disabled = false;
                    cell.classList.remove('x', 'o', 'winner');
                });
            }
        }
