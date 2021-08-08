import React from 'react';
import Square from './Square';


class Board extends React.Component
{
    renderSquare(i)
    {
        return <Square value={i} />
    }

    render() {
        const status = 'Next player: X';
    
        return (
          <div class = "board">
            <p className="status">{status}</p>
            <button className = "start-new-game">Start a new game</button>
            <div className="board-row">
              {this.renderSquare(0)}
              {this.renderSquare(1)}
              {this.renderSquare(2)}
            </div>
            <div className="board-row">
              {this.renderSquare(3)}
              {this.renderSquare(4)}
              {this.renderSquare(5)}
            </div>
            <div className="board-row">
              {this.renderSquare(6)}
              {this.renderSquare(7)}
              {this.renderSquare(8)}
            </div>
          </div>
        );
    }
}

export default Board;