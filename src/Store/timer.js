const initialState = { currentTime: '', username: 'Alex' };
  

const timerReducer = (state = initialState, action) => {
  if (action.type === 'setTokenTimeValues') {
    return {
      ...action
    };
  }
  if (action.type === 'setCurrentTime') {
    return {
      ...state,
      currentTime: action.payload,
    };
  }
  
  return state;
};

export default timerReducer;
