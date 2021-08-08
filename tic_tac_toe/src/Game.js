import React from 'react';
import Board from './Board';

function calculateWinner(squares) {
    const lines = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [0, 4, 8],
      [2, 4, 6],
    ];
    for (const line of lines) {
      const [a, b, c] = line;
      if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
        return squares[a];
      }
    }
    return null;
}

class Game extends React.Component
{
    constructor(props) {
        super(props);
        this.state = {
          history: [{
            squares: Array(9).fill(null),
          }],
          xIsNext: true,
        };
    }

    restartGame()
    {
        this.setState({
            history: [{
                squares: Array(9).fill(null),
            }],
            xIsNext: true,
        });
    }

    handleClick(i)
    {
        const history = this.state.history;
        const current = history[history.length - 1];
        const squares = current.squares.slice();
        if (calculateWinner(squares) || squares[i])
        {
            return;
        }
        squares[i] = this.state.xIsNext ? 'X' : 'O';
        this.setState({
            history: history.concat([{
                squares: squares,
            }]),
            squares,
            xIsNext: !this.state.xIsNext
        });
    }

    render() {
        const history = this.state.history;
        const current = history[history.length - 1];
        const winner = calculateWinner(current.squares);
        let status;
        if (winner) {
            status = 'Winner: ' + winner;
        } 
        else if (current.squares.indexOf(null) === -1)
        {
            status = 'Its a draw';
        }
        else 
        {
            status = 'Next player: ' + (this.state.xIsNext ? 'X' : 'O');
        }
        return (
          <div className="game">
            <div className="game-board">
            <p className="status">{status}</p>
            <button className = "start-new-game" onClick={() => this.restartGame()}>Start a new game</button>
              <Board 
                squares={current.squares}
                onClick={(i) => this.handleClick(i)}
              />
            </div>
            <div className="game-info">
              <ol>{/* TODO */}</ol>
            </div>
          </div>
        );
      }
}

export default Game;