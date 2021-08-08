import React from 'react';

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

function Square(props)
{
    return (
        <button className = {"square " + props.bg} onClick={props.onClick}>
            {props.value}
        </button>
    )
}

class Board extends React.Component
{
    constructor(props)
    {
        super(props);
        this.state = {
            squares: Array(9).fill(null),
            xIsNext: true
        };
    }

    restartGame()
    {
        this.setState({
            squares: Array(9).fill(null),
            xIsNext: true
        });
    }

    handleClick(i)
    {
        const squares = this.state.squares.slice();
        if (calculateWinner(squares) || squares[i])
        {
            return;
        }
        squares[i] = this.state.xIsNext ? 'X' : 'O';
        this.setState({
            squares,
            xIsNext: !this.state.xIsNext
        });
    }

    renderSquare(i)
    {
        let bg;
        if ( this.state.squares[i] === 'O')
        {
            bg = 'square-o';
        }
        else if (this.state.squares[i] === 'X')
        {
            bg = 'square-x';
        }

        return <Square 
        value={this.state.squares[i]}
        onClick={() => { this.handleClick(i); }} 
        bg={bg}/>
    }

    render() {
        const winner = calculateWinner(this.state.squares);
        let status;
        if (winner)
        {
            status = 'Winner: ' + winner;
        }
        else
        {
            status = 'Next player: ' + (this.state.xIsNext ? 'X' : 'O');
        }
    
        return (
          <div class = "board">
            <p className="status">{status}</p>
            <button className = "start-new-game" onClick={() => this.restartGame()}>Start a new game</button>
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