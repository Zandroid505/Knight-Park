import "./App.css";
import DropDown from "./components/DropDown/DropDown";
import Garage from "./components/Garage/Garage";

function App() {
  return (
    <div class="container-fluid text-center">
      <div class="top-container">
        <div class="row">
          <h1>Knight Park</h1>
          <DropDown></DropDown>
        </div>
      </div>

      <div class="middle-container">
        <Garage></Garage>
        <div class="row">
          <div class="col garage"></div>
          <div class="col garage">
            <h2>Garage B</h2>
          </div>
        </div>
        <div class="row">
          <div class="col">
            <h3>Floor 1</h3>
          </div>
          <div class="col">
            <h3>Floor 2</h3>
          </div>
        </div>
        <div class="row">
          <div class="col num-of-cars">
            <h4>6/6</h4>
          </div>
          <div class="col num-of-cars">
            <h4>3/6</h4>
          </div>
        </div>
      </div>

      <div class="bottom-container">
        <p class="copyright">©Knight Park Incorporated</p>
      </div>
    </div>
  );
}

export default App;
