open Jest;
open ExpectJs;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

let renderReason = (genericAction, genericCallback) =>
  <div>
    <Reactour
      steps=Reactour.Steps.Step.[
        {
          selector: "#cta",
          content: `element(<> {"Click this!" |> React.string} </>),
          position: `right,
          action: genericAction,
          style: ReactDOMRe.Style.make(),
          stepInteraction: true,
          navDotAriaLabel: "",
        },
      ]
      isOpen=true
      onRequestClose=genericCallback
    />
  </div>
  |> Enzyme.shallow
  |> Enzyme.Shallow.childAt(0);

let renderJs = [%bs.raw
  "(genericCallback) => React.createElement(require('reactour').default, {
  steps: [{
      selector: '#cta',
      content: React.createElement(React.Fragment, undefined, 'Click this!'),
      position: 'right',
      action: genericCallback,
      style: {},
      stepInteraction: true,
      navDotAriaLabel: '',
    }],
  isOpen: true,
  onRequestClose: genericCallback
})"
];

describe("Reactour", () => {
  test("output equal to direct JS rendering", () => {
    let genericCallback = [%bs.raw "() => {}"];
    let reasonComponent = renderReason(genericCallback, genericCallback);
    let jsComponent = [%bs.raw "renderJs(genericCallback, genericCallback)"];

    expect(Enzyme.Shallow.equals(jsComponent, reasonComponent))
    |> toBe(true);
  })
});
