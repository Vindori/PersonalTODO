import {component$, useMount$, useStore} from '@builder.io/qwik';
import type {DocumentHead} from '@builder.io/qwik-city';
import axios from "axios";

export const URL = 'http://localhost:8000'

axios.defaults.baseURL = URL;
axios.defaults.headers.post['Content-Type'] ='application/json;charset=utf-8';
axios.defaults.headers.post['Access-Control-Allow-Origin'] = '*';

interface Todo {
  todo_id: number
  title: string
  done: boolean
}

export async function updateTodo(todo: Todo) {
  let res = (await axios.put(`${URL}/todo/${todo.todo_id}`, todo)).data
  console.log(res);
}


export default component$(() => {
  const state = useStore<{todos: Todo[], newTodo: string}>({
    todos: [
      {todo_id: 1, title: 'Помыть посуду', done: true},
      {todo_id: 2, title: 'Выгулять собаку', done: false},
      {todo_id: 3, title: 'Сделать курсач', done: false},

    ],
    newTodo: '',
  }, {recursive: true});


  useMount$(async () => {
    state.todos = (await axios.get(`${URL}/todo`)).data.items;
  })

  return (
    <div class="flex flex-col items-center artboard phone-2 rounded-lg bg-primary-content">
      <div class="flex justify-center py-4 bg-primary/60 w-full">
        <h1 class="text-center font-bold uppercase text-xl text-primary-content">
          Личный список дел
        </h1>
      </div>
      <div className="flex align-center p-3">
        <label htmlFor="my-modal-4" className="btn btn-accent modal-button">Новая задача</label>
      </div>
      <div class="w-full px-5 my-4 overflow-y-auto">
        <div class="w-full font-bold">
          {
            state.todos.filter(todo => !todo.done).length ?
              <h2>Предстоит сделать:</h2>
              :
              <h2>Здесь пусто</h2>
          }

        </div>

        <div class="my-3">
          {state.todos.map(todo => (
            !todo.done ?
              <div className="flex justify-between my-1" key={todo.title}>
                <input type="text" value={todo.title} onChange$={(e) => {todo.title = e.target.value || ''; updateTodo(todo)}}/>
                <input type="checkbox" checked={todo.done} onClick$={() => {todo.done = !todo.done; updateTodo(todo)}}/>
              </div> : <></>
          ))}
        </div>

        <hr class="border border-accent-content/10 w-full"/>
        <div class="w-full font-bold py-4">
          {
            state.todos.filter(todo => todo.done).length ?
              <h2>Выполнено:</h2>
              :
              <h2>Пока пусто</h2>

          }
        </div>
        <div>
          {state.todos.map(todo => (
            todo.done ?
              <div class="flex justify-between my-1">
                <input class="text-accent-content/50" type="text" value={todo.title} onChange$={(e) => {todo.title = e.target.value || ''; updateTodo(todo)}}/>
                <input type="checkbox" checked={todo.done} onClick$={() => {todo.done = !todo.done; updateTodo(todo)}}/>
              </div> : <></>
          ))}
        </div>

        <div>
          <input type="checkbox" id="my-modal-4" className="modal-toggle"/>
          <label htmlFor="my-modal-4" className="modal cursor-pointer">
            <label className="modal-box relative flex flex-col items-center" htmlFor="">
              <h3 class="text-center p-3 font-bold text-xl">Добавить задачу</h3>
              <input type="text" class="input w-5/6 my-3" placeholder="Моя новая задача" value={state.newTodo} onChange$={(e) => state.newTodo = e.target.value || ''}/>

              <label htmlFor="my-modal-4"  class="btn btn-primary my-4" onClick$={async () => {
                if (state.newTodo !== '') {
                  const newTodoObj = {todo_id: 0, title: state.newTodo, done: false};
                  state.todos = state.todos.concat([newTodoObj])
                  console.log((await axios.post(`${URL}/todo/`, newTodoObj)).data)
                }

              }}>Создать</label>
            </label>
          </label>
        </div>
      </div>
    </div>
  );
});

export const head: DocumentHead = {
  title: 'Welcome to Qwik',
};
