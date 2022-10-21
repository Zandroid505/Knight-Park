import Floor from "../Floor/Floor";
import "./Garage.css";

const Garage = () => {
  return (
    <div>
      <h2>Garage A</h2>
      <div class="col">
        <Floor></Floor>
      </div>
      <div class="col">
        <h3>Floor 2</h3>
        <div class="col num-of-cars">
          <h4>4/6</h4>
        </div>
      </div>
    </div>
  );
};

export default Garage;
