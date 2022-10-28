function Floor(props) {
  const NumFloors = props.numFloors;

  const final = [];

  return (
    <div class="row">
      <div class="col">
        <h3>Floor 1</h3>
        <div class="col num-of-cars">
          <h4>4/6</h4>
        </div>
        <div>Hello {NumFloors}</div>
      </div>
    </div>
  );
}

export default Floor;
