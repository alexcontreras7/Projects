import { createTheme, makeStyles } from '@material-ui/core/styles';
import { blue, red, grey } from '@material-ui/core/colors';

const styles = {
  theme: createTheme({
    typography: {
      fontFamily: 'ember',
      h1: {
        fontSize: 18,
      },
      h2: {
        fontSize: 17,
      },
    },
    palette: {
      primary: {
        main: blue[500],
      },
    },
  }),

  useStyles: makeStyles((theme) => ({
    root: {
      padding: '0px 0px',
      margin: '25px',
      boxShadow: '0 1px 12px rgba(2, 2, 2, 2)',
      borderRadius: '0px',
      width: '500px',
      height: '160px',
      float: 'left',
    },
    appBar: {
      height: '100px', 
      backgroundImage: `linear-gradient(to bottom right, ${grey[900]} 0%, ${grey[900]} 50%, ${red[700]} 50%, ${red[700]} 100%)`,
      boxShadow: '0px 4px 10px rgba(0, 0, 0, 0.1)',
    },
    
    button: {
      background: 'linear-gradient(45deg, #6BA4FE, #6BE2FE)',
      border: 0,
      marginTop: theme.spacing(1),
      color: grey[50],
      padding: theme.spacing(1.5, 2),
    },
    dataBtn: {
      marginRight: theme.spacing(2),
      color: theme.palette.common.white,
      fontWeight: 'bold',
    },
    titleContainer: {
      flex: 1,
      display: 'flex',
      justifyContent: 'flex-start',
    },
    infoContainer: {
      display: 'flex',
      justifyContent: 'flex-end',
      alignItems: 'center',
    },
    title: {
      marginRight: theme.spacing(2),
      color: 'white',
    },
    infoText: {
      color: 'white',
    },
    toolbar: {
      display: 'flex',
      flexDirection: 'row',
      justifyContent: 'space-between',
    },    
    searchContainer: {
      display: 'flex',
      alignItems: 'center',
      flex: 1,
    },
    searchWrapper: {
      display: 'flex',
      alignItems: 'center',
    },
    searchBar: {
      display: 'flex',
      alignItems: 'center',
      //backgroundImage: `linear-gradient(to bottom right, ${grey[900]} 0%, ${grey[900]} 50%, ${red[700]} 50%, ${red[700]} 100%)`,
      padding: '24px 16px',
      borderRadius: 25,
      flex: 1,
    },
    searchInput: {
      marginRight: 8,
      backgroundColor: theme.palette.common.white,
      borderRadius: theme.shape.borderRadius,
      flex: 1,
    },
    searchIcon: {
      color: 'white', // or any desired color
    },
    searchButton: {
      backgroundColor: theme.palette.common.white,
      color: 'white', // or 'grey[50]'
    },
    link: {
      margin: theme.spacing(1, 1.5),
    },
    navLink: {
      textDecoration: 'none',
      color: 'inherit',
    },
    productPage: {
      background: 'burgundy',
      padding: '20px',
    },
    productContainer: {
      display: 'flex',
      alignItems: 'center',
      padding: '10px',
      border: '1px solid #ccc',
      borderRadius: '4px',
      marginBottom: '20px',
      background: red[700],
    },
    productImage: {
      width: '100px',
      height: '150px',
      paddingTop: '20px'
    },
    productDetails: {
      marginLeft: '20px',
    },
  })),
};

function SetStyle() {
  return styles;
}

export default SetStyle;
