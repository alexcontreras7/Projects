import React from 'react';
import SetStyle from '../UI/SetStyle';
import TextField from '@material-ui/core/TextField';
import IconButton from '@material-ui/core/IconButton';
import SearchIcon from '@material-ui/icons/Search';



const { useStyles } = SetStyle();

const SearchBar = () => {
    const classes = useStyles();

    const handleSearch = () => {
      // Handle search functionality here
    };
  
    return (
        <div className={classes.searchBarContainer}>
          <div className={classes.searchBar}>
            <TextField
              className={classes.searchInput}
              variant="outlined"
              placeholder="Search..."
            />
            <IconButton
              className={classes.searchButton}
              onClick={handleSearch}
            >
              <SearchIcon 
                className={classes.searchIcon}
              />
            </IconButton>
          </div>
        </div>
      );
    }

export default SearchBar;
