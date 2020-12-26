# bs-reactour

[![Build Status](https://travis-ci.com/erykpiast/bs-reactour.svg?branch=master)](https://travis-ci.com/erykpiast/bs-reactour)
[![dependencies Status](https://david-dm.org/erykpiast/bs-reactour/status.svg)](https://david-dm.org/erykpiast/bs-reactour)
[![devDependencies Status](https://david-dm.org/erykpiast/bs-reactour/dev-status.svg)](https://david-dm.org/erykpiast/bs-reactour?type=dev)
[![peerDependencies Status](https://david-dm.org/erykpiast/bs-reactour/peer-status.svg)](https://david-dm.org/erykpiast/bs-reactour?type=peer)
[![Greenkeeper badge](https://badges.greenkeeper.io/erykpiast/bs-reactour.svg)](https://greenkeeper.io/)

ReasonML bindings for [reactour](https://github.com/praneshr/reactour) library. JSX 3 syntax only.

## Installation

```
npm i --save bs-reactour reactour
```

Then add `bs-reactour` as a dependency to `bsconfig.json`.

## Usage

```reasonml
[@react.component]
let make = () => {
  let (isOpen, setIsOpen) = React.useState(() => true);
  let handleClose =
    React.useCallback1(() => setIsOpen(_ => false), [|setIsOpen|]);

  <Reactour
    isOpen
    steps={Reactour.Steps.Step.[{
      selector: "#cta",
      content: `element(<>{"Click this!" |> React.string}</>),
      position: `right,
      action: _ => {
        Js.log("The first step entered!")
      },
      style: ReactDOMRe.Style.make(),
      stepInteraction: true,
      navDotAriaLabel: "",
    }, {
      selector: "#modal",
      content: `element(<>{"You made this thing to pop up!" |> React.string}</>),
      position: `left,
      action: _ => {
        Js.log("The second step entered!")
      },
      style: ReactDOMRe.Style.make(
        ~width="300px",
        ()
      ),
      stepInteraction: false,
      navDotAriaLabel: "",
    }]}
    onRequestClose=handleClose
  />;;
};
```
