import React from 'react';
import image1 from '../image1.png';
import image2 from '../image2.png';

function About() {
  return (
    <div>
      <h1 style={{ color: 'white' }}>About Us</h1>
      <p>Some information about us...</p>

      <div style={{ display: 'flex', justifyContent: 'space-between' }}>
        <div style={{ flex: 1, padding: '10px' }}>
          <img src={image1} alt="description of image1" style={{ width: '100%', height: '70%', objectFit: 'cover' }} />
          <p style={{ color: 'white' }} >Alex</p>
        </div>

        <div style={{ flex: 1, padding: '10px' }}>
          <img src={image2} alt="description of another image2" style={{ width: '100%', height: '70%', objectFit: 'cover' }} />
          <p style={{ color: 'white' }} >Faaris</p>
        </div>
      </div>
    </div>
  );
}



  
  export default About;
