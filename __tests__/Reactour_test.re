open Jest;
open ExpectJs;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

let renderReason = (onRequestClose, steps) =>
  <div> <Reactour steps isOpen=true onRequestClose /> </div>
  |> Enzyme.shallow
  |> Enzyme.Shallow.childAt(0);

let renderJs = [%bs.raw
  "(onRequestClose, steps) => React.createElement(require('reactour').default, {
  steps,
  isOpen: true,
  onRequestClose
})"
];

describe("Reactour", () => {
  test("output equal to direct JS rendering", () => {
    let onRequestClose = () => ();
    let action = _ => ();
    let renderStep = () => <div> {"Baz" |> React.string} </div>;

    let reasonComponent =
      renderReason(
        onRequestClose,
        [
          Reactour.Steps.Step.{
            selector: ".foobar",
            content: `element(<div> {"Foobar" |> React.string} </div>),
            position: `top,
            action,
            style: ReactDOMRe.Style.make(),
            stepInteraction: true,
            navDotAriaLabel: "",
          },
          Reactour.Steps.Step.{
            selector: "#baz",
            content: `func(renderStep),
            position: `coords((1, 2)),
            action,
            style: ReactDOMRe.Style.make(~color="red", ()),
            stepInteraction: false,
            navDotAriaLabel: "the-label",
          },
        ],
      );
    let jsComponent = [%bs.raw
      "renderJs(onRequestClose, [
          {
              selector: '.foobar',
              content: React.createElement('div', {}, 'Foobar'),
              position: 'top',
              action,
              style: {},
              stepInteraction: true,
              navDotAriaLabel: ''
            },
            {
              selector: '#baz',
              content: renderStep,
              position: [1, 2],
              action,
              style: { color: 'red' },
              stepInteraction: false,
              navDotAriaLabel: 'the-label'
            }
        ])"
    ];

    expect(Enzyme.Shallow.equals(jsComponent, reasonComponent))
    |> toBe(true);
  })
});
