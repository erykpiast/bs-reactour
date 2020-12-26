module AccessibilityOptions = {
  type t = {
    ariaLabelledBy: string,
    closeButtonAriaLabel: string,
    showNavigationScreenReaders: bool,
  };

  type js = {
    .
    "ariaLabelledBy": string,
    "closeButtonAriaLabel": string,
    "showNavigationScreenReaders": bool,
  };

  let toJs = options => {
    "ariaLabelledBy": options.ariaLabelledBy,
    "closeButtonAriaLabel": options.closeButtonAriaLabel,
    "showNavigationScreenReaders": options.showNavigationScreenReaders,
  };
};

module KeyboardNavigation = {
  type js;

  module Key = {
    type t = [ | `esc | `right | `left];

    external stringToJs: string => js = "%identity";

    let toJs =
      fun
      | `esc => "esc" |> stringToJs
      | `right => "right" |> stringToJs
      | `left => "left" |> stringToJs;
  };

  module All = {
    type t = bool;

    external toJs: bool => js = "%identity";
  };

  type t = [ | `key(Key.t) | `all(All.t)];

  let make =
    fun
    | `key(key) => key |> Key.toJs
    | `all(all) => all |> All.toJs;
};

module Steps = {
  module Content = {
    module Params = {
      // TODO: type as { goTo: int => unit, close: 'a => unit, inDOM: bool, step: int }
      type t = unit;
    };

    type t = [
      | `node(Dom.node)
      | `element(React.element)
      | `func(Params.t => React.element)
    ];

    type js;

    external nodeToJs: Dom.node => js = "%identity";
    external elementToJs: React.element => js = "%identity";
    external funcToJs: (Params.t => React.element) => js = "%identity";

    let toJs =
      fun
      | `node(node) => node |> nodeToJs
      | `element(element) => element |> elementToJs
      | `func(func) => func |> funcToJs;
  };

  module Position = {
    type t = [
      | `top
      | `right
      | `bottom
      | `left
      | `center
      | `coords(int, int)
    ];

    type js;

    external stringToJs: string => js = "%identity";
    external arrayToJs: array(int) => js = "%identity";

    let toJs =
      fun
      | `top => "top" |> stringToJs
      | `right => "right" |> stringToJs
      | `bottom => "bottom" |> stringToJs
      | `left => "left" |> stringToJs
      | `center => "center" |> stringToJs
      | `coords(x, y) => [|x, y|] |> arrayToJs;
  };

  module Step = {
    type t = {
      selector: string,
      content: Content.t,
      position: Position.t,
      action: Dom.node => unit,
      style: ReactDOMRe.style,
      stepInteraction: bool,
      navDotAriaLabel: string,
    };

    type js = {
      .
      "selector": string,
      "content": Content.js,
      "position": Position.js,
      "action": Dom.node => unit,
      "style": ReactDOMRe.style,
      "stepInteraction": bool,
      "navDotAriaLabel": string,
    };

    let toJs = step => {
      "selector": step.selector,
      "content": step.content |> Content.toJs,
      "position": step.position |> Position.toJs,
      "action": step.action,
      "style": step.style,
      "stepInteraction": step.stepInteraction,
      "navDotAriaLabel": step.navDotAriaLabel,
    };
  };

  type t = list(Step.t);

  type js = array(Step.js);

  let toJs = steps => steps |> List.map(Step.toJs) |> Array.of_list;
};

[@bs.module "reactour"] [@react.component]
external make:
  (
    ~accentColor: string=?,
    ~accessibilityOptions: AccessibilityOptions.js=?,
    ~badgeContent: (int, int) => React.element=?,
    ~className: string=?,
    ~closeWithMask: bool=?,
    ~disableDotsNavigation: bool=?,
    ~disableInteraction: bool=?,
    ~disableKeyboardNavigation: KeyboardNavigation.js=?,
    ~getCurrentStep: int => React.element=?,
    ~goToStep: int=?,
    ~highlightedMaskClassName: string=?,
    ~inViewThreshold: int=?,
    ~isOpen: bool,
    ~lastStepNextButton: Dom.node=?,
    ~maskClassName: string=?,
    ~maskSpace: int=?,
    ~nextButton: Dom.node=?,
    ~nextStep: unit => unit=?,
    ~onAfterOpen: Dom.node => unit=?,
    ~onBeforeClose: Dom.node => unit=?,
    ~onRequestClose: unit => unit,
    ~prevButton: React.element=?,
    ~prevStep: unit => unit=?,
    ~rounded: int=?,
    ~scrollDuration: int=?,
    ~scrollOffset: int=?,
    ~showButtons: bool=?,
    ~showCloseButton: bool=?,
    ~showNavigation: bool=?,
    ~showNavigationNumber: bool=?,
    ~showNumber: bool=?,
    ~startAt: int=?,
    ~steps: Steps.js,
    ~update: string=?,
    ~updateDelay: int=?
  ) =>
  React.element =
  "default";

let makeProps =
    (
      ~accentColor=?,
      ~accessibilityOptions=?,
      ~badgeContent=?,
      ~className=?,
      ~closeWithMask=?,
      ~disableDotsNavigation=?,
      ~disableInteraction=?,
      ~disableKeyboardNavigation=?,
      ~getCurrentStep=?,
      ~goToStep=?,
      ~highlightedMaskClassName=?,
      ~inViewThreshold=?,
      ~isOpen,
      ~lastStepNextButton=?,
      ~maskClassName=?,
      ~maskSpace=?,
      ~nextButton=?,
      ~nextStep=?,
      ~onAfterOpen=?,
      ~onBeforeClose=?,
      ~onRequestClose,
      ~prevButton=?,
      ~prevStep=?,
      ~rounded=?,
      ~scrollDuration=?,
      ~scrollOffset=?,
      ~showButtons=?,
      ~showCloseButton=?,
      ~showNavigation=?,
      ~showNavigationNumber=?,
      ~showNumber=?,
      ~startAt=?,
      ~steps,
      ~update=?,
      ~updateDelay=?,
    ) =>
  makeProps(
    ~accentColor?,
    ~accessibilityOptions?,
    ~badgeContent?,
    ~className?,
    ~closeWithMask?,
    ~disableDotsNavigation?,
    ~disableInteraction?,
    ~disableKeyboardNavigation?,
    ~getCurrentStep?,
    ~goToStep?,
    ~highlightedMaskClassName?,
    ~inViewThreshold?,
    ~isOpen,
    ~lastStepNextButton?,
    ~maskClassName?,
    ~maskSpace?,
    ~nextButton?,
    ~nextStep?,
    ~onAfterOpen?,
    ~onBeforeClose?,
    ~onRequestClose,
    ~prevButton?,
    ~prevStep?,
    ~rounded?,
    ~scrollDuration?,
    ~scrollOffset?,
    ~showButtons?,
    ~showCloseButton?,
    ~showNavigation?,
    ~showNavigationNumber?,
    ~showNumber?,
    ~startAt?,
    ~steps=steps |> Steps.toJs,
    ~update?,
    ~updateDelay?,
  );
