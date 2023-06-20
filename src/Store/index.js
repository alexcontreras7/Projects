import { combineReducers, createStore, applyMiddleware } from 'redux';
import thunk from 'redux-thunk';
import timerReducer from './timer';

const allReducers = combineReducers({
  timer: timerReducer
});

const store = createStore(
    allReducers,
    applyMiddleware(thunk)
    );

export default store;