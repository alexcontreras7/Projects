import React from 'react';

import image1 from '../image1.png';
import image2 from '../image2.png';
import SetStyle from '../UI/SetStyle';



function Products() {
  const products = [
    {
      id: 1,
      image: image1,
      title: 'Product 1',
      description: 'Description of Product 1',
      price: 19.99,
    },
    {
      id: 2,
      image: image2,
      title: 'Product 2',
      description: 'Description of Product 2',
      price: 24.99,
    },
    // Add more products as needed
  ];

  const { useStyles } = SetStyle();
  const classes = useStyles();

  return (
    <div>
      <h1 style={{ color: 'white' }}>Products</h1>
      {products.map((product) => (
        <div key={product.id} className={classes.productContainer}>   
          <img src={product.image} alt={product.title} className={classes.productImage} />
          <div className={classes.productDetails}>
            <h3>{product.title}</h3>
            <p>{product.description}</p>
            <p>Price: ${product.price}</p>
            <button className={classes.button}>Buy Now</button>
          </div>
        </div>
      ))}
    </div>
  );
}

export default Products;
