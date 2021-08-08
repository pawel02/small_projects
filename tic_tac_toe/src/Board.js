import React from 'react';

function Square(props)
{
    return (
        <button className = "square" onClick={props.onClick}>
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

    handleClick(i)
    {
        const squares = this.state.squares.slice();
        squares[i] = this.state.xIsNext ? 'X' : 'O';
        this.setState({
            squares,
            xIsNext: !this.state.xIsNext
        });
    }

    renderSquare(i)
    {
        return <Square 
        value={this.state.squares[i]}
        onClick={() => { this.handleClick(i); }} />
    }

    render() {
        const status = 'Next player: ' + (this.state.xIsNext ? 'X' : 'O');
    
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