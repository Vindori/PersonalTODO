import {component$, Slot} from '@builder.io/qwik';

export default component$(() => {
  return (
    <>
      <main className="w-full h-screen grid place-items-center bg-accent-content/5">
        <Slot/>
      </main>
    </>
  );
});
