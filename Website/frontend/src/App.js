import "./App.css";
import DropDown from "./components/DropDown/DropDown";
import Garage from "./components/Garage/Garage";

function App() {
  return (
    <div class="container-fluid text-center">
      <div class="top-container">
        <div class="row">
          <h1>Test</h1>
          <DropDown></DropDown>
        </div>
      </div>

      <div class="middle-container">
        <div class="row">
          <div class="col garage">
            <Garage name="Garage A" numFloors="5"></Garage>
          </div>

          <div class="col garage">
            <Garage name="Garage B" numFloors="6"></Garage>
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
