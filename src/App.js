import React, { FC } from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import NavBar from './NavigationBar/navbar';
import Product from './Pages/Product';
import About from './Pages/About';
import Home from './Pages/Home';
import { RedirectComponent } from './components/RedirectComponent';


const App: FC = () => {
  return (
    <div className="App" style={{ backgroundColor: 'black' }}>
      <header className="App-header">
        <Router>
      <div>
        <NavBar />
        <Routes>
          <Route path="/home" element={<Home />} />
          <Route path="/product" element={<Product />} />
          <Route path="/about" element={<About />} />
          <Route path="/" element={<RedirectComponent />} />
        </Routes>
      </div>
    </Router>
      </header>
    </div>
  );
}

export default App;
