import React, { useEffect } from 'react';
import Typography from '@material-ui/core/Typography';
import { useDispatch, useSelector } from 'react-redux';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Box from '@material-ui/core/Box';
import SetStyle from '../UI/SetStyle';
import { updateTime } from './timeUtils';
import { Link } from 'react-router-dom';

const NavBar = () => {
  const { useStyles } = SetStyle();
  const classes = useStyles();
  const currentTime = useSelector((state) => state.timer.currentTime);
  const username = useSelector((state) => state.timer.username);
  const dispatch = useDispatch();

  useEffect(() => {
    const timerId = updateTime(dispatch);

    // Clear the interval when the component is unmounted
    return () => clearInterval(timerId);
  }, [dispatch]);

  return (
    <AppBar position="static" className={classes.appBar}>
      <Toolbar className={classes.toolbar} style={{ justifyContent: 'space-between' }}>
        <Box className={classes.titleContainer} style={{ flex: 1 }}>
          <Typography variant="h6" className={classes.title} component="h1">
            KoolKidKlub
          </Typography>
        </Box>

        <div style={{ display: 'flex', justifyContent: 'center', width: '200px' }}>
          <Typography variant="h6" style={{margin: '0 10px'}}>
            <Link to="/" style={{textDecoration: 'none', color: 'blue'}}>Home</Link>
          </Typography>
          <Typography variant="h6" style={{margin: '0 10px'}}>
            <Link to="/product" style={{textDecoration: 'none', color: 'blue'}}>Product</Link>
          </Typography>
          <Typography variant="h6" style={{margin: '0 10px'}}>
            <Link to="/about" style={{textDecoration: 'none', color: 'blue'}}>About</Link>
          </Typography>
        </div>

        <Box className={classes.infoContainer} style={{ flex: 1, display: 'flex', justifyContent: 'flex-end' }}>
          <Typography variant="body1" className={classes.infoText}>
            {username} {currentTime}
          </Typography>
        </Box>
      </Toolbar>
    </AppBar>
  );
}

export default NavBar;
