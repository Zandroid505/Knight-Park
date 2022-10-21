import { useState } from "react";

const DropDown = () => {
  const [expand, setExpand] = useState(false);
  const toggleExpand = () => setExpand((prevExpand) => !prevExpand);
  console.log(expand);

  return (
    <div>
      <button onClick={toggleExpand}>Choose Garage</button>
      {expand && (
        <div>
          <div>Garage A</div>
          <div>Garage B</div>
        </div>
      )}
    </div>
  );
};

export default DropDown;
