import { setCurrentTime } from '../Actions/setCurrentTime';

export const updateTime = (dispatch) => {
  return setInterval(() => {
    const currentTime = new Date();
    const options = {
      hour: 'numeric',
      minute: '2-digit',
      second: '2-digit',
      hour12: true,
    };
    const formattedTime = currentTime.toLocaleTimeString(undefined, options);

    dispatch(setCurrentTime(formattedTime));
  }, 1000);
};
