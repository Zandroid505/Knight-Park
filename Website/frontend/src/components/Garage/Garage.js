import Floor from "../Floor/Floor";
import "./Garage.css";

const Garage = (props) => {
  return (
    <div>
      <h2>{props.name}</h2>
      <div class="col">
        <Floor numFloors={props.numFloors}></Floor>
      </div>
    </div>
  );
};

export default Garage;
