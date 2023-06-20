export const setCurrentTime = (time) => {
    return (dispatch) => {
      dispatch({ type: 'setCurrentTime', payload: time });
    };
  };
  