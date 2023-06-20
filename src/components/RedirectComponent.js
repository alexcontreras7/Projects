import { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';

export function RedirectComponent() {
  const navigate = useNavigate();

  useEffect(() => {
    navigate('/home');
  }, [navigate]);

  return null;
}
