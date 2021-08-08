import React from 'react';

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
    renderSquare(i)
    {
        let bg;
        if ( this.props.squares[i] === 'O')
        {
            bg = 'square-o';
        }
        else if (this.props.squares[i] === 'X')
        {
            bg = 'square-x';
        }

        return <Square 
                value={this.props.squares[i]}
                onClick={() => { this.props.onClick(i); }} 
                bg={bg}
            />
    }

    render() {
        return (
          <div class = "board">
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